/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_power.h"

#include "app_error.h"
#include "app_util.h"
#include "app_usbd_core.h"
#include "app_usbd.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_cdc_acm.h"
#include "app_usbd_serial_num.h"

#include "boards.h"
#include "bsp.h"
#include "bsp_cli.h"
#include "nrf_cli.h"
#include "nrf_cli_uart.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "ringbuf.h"
#include "math.h"


#include "rt_nonfinite.h"
#include "time_domain.h"

#include "freq_domain.h"
#include <string.h>

#include "classifyX.h"




/**
 * @brief CLI interface over UART
 */
NRF_CLI_UART_DEF(m_cli_uart_transport, 0, 64, 16);
NRF_CLI_DEF(m_cli_uart,
            "uart_cli:~$ ",
            &m_cli_uart_transport.transport,
            '\r',
            4);



/**@file
 * @defgroup usbd_cdc_acm_example main.c
 * @{
 * @ingroup usbd_cdc_acm_example
 * @brief USBD CDC ACM example
 *
 */

#define LED_USB_RESUME      (BSP_BOARD_LED_0)
#define LED_CDC_ACM_OPEN    (BSP_BOARD_LED_1)
#define LED_CDC_ACM_RX      (BSP_BOARD_LED_2)
#define LED_CDC_ACM_TX      (BSP_BOARD_LED_3)

#define BTN_CDC_DATA_SEND       0
#define BTN_CDC_NOTIFY_SEND     1

#define BTN_CDC_DATA_KEY_RELEASE        (bsp_event_t)(BSP_EVENT_KEY_LAST + 1)
#define fea_vec_frame 6
#define SAMPLES_PER_FRAME 12
#define proc_frame 400
#define VREF 5

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif


static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event);

#define CDC_ACM_COMM_INTERFACE  0
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE  1
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT1


/**
 * @brief CDC_ACM class instance
 * */
APP_USBD_CDC_ACM_GLOBAL_DEF(m_app_cdc_acm,
                            cdc_acm_user_ev_handler,
                            CDC_ACM_COMM_INTERFACE,
                            CDC_ACM_DATA_INTERFACE,
                            CDC_ACM_COMM_EPIN,
                            CDC_ACM_DATA_EPIN,
                            CDC_ACM_DATA_EPOUT,
                            APP_USBD_CDC_COMM_PROTOCOL_AT_V250
);


#define ENDLINE_STRING "\r\n"
#define RINGBUF_SIZE 1024 //buffering data, must be power of 2!
#define EEG_FRAME_SIZE 216  //8 lots of 27 bytes
#define READ_SIZE 256 //max size of USB packet. Must be > 216 bytes
#define DATA_BUFFER_SIZE 1024

static char m_rx_buffer[2][READ_SIZE];
static char m_tx_buffer[NRF_DRV_USBD_EPSIZE];
static bool m_send_flag = 0;
static volatile uint8_t m_active_buffer;

struct ringbuf eegRing;
static uint8_t ringBuffer[RINGBUF_SIZE];
static double tem[8] = {0};
static uint8_t debugBuff [EEG_FRAME_SIZE] = {0};
static uint8_t flag = 0;


void process_packet(char * m_rx_buffer)
{
	for (int i=0; i<EEG_FRAME_SIZE; i++){
		ringbuf_put( &eegRing, m_rx_buffer[i]);
	}
}

int receive_packet(int idx){ // try using flag
	int p=0;
	int k=0;
	uint32_t val = 0;
	int32_t i=0;
	while (ringbuf_elements(&eegRing) > 0){
	        	debugBuff[idx++] = ringbuf_get(&eegRing); //gets 1 byte at a time .
	        }
    if (idx>0){
        for(p=3;p<217;p+=27){
        	val = debugBuff[p] << 24;
        	val = val + (debugBuff[p+1] << 16);
        	i = (int32_t) (val + (debugBuff[p+2] << 8));
        	tem[k] =(float) (i);
        	tem[k] = tem[k]* 2 * VREF / (12*pow(2,32));
        	k += 1;
        }
    }
    return flag=1;
}






/**
 * @brief User event handler @ref app_usbd_cdc_acm_user_ev_handler_t (headphones)
 * */
static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = app_usbd_cdc_acm_class_get(p_inst);

    switch (event)
    {
        case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
        {
            bsp_board_led_on(LED_CDC_ACM_OPEN);

            /*Setup first transfer*/
            m_active_buffer=0;
            ret_code_t ret = app_usbd_cdc_acm_read(&m_app_cdc_acm,
                                                   m_rx_buffer[m_active_buffer],
                                                   READ_SIZE);
            ret = app_usbd_cdc_acm_read(&m_app_cdc_acm,
												   m_rx_buffer[1],
												   READ_SIZE); //double buffer

            UNUSED_VARIABLE(ret);
            break;
        }
        case APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE:
            bsp_board_led_off(LED_CDC_ACM_OPEN);
            break;
        case APP_USBD_CDC_ACM_USER_EVT_TX_DONE:
            bsp_board_led_invert(LED_CDC_ACM_TX);
            NRF_LOG_INFO("frame sent");
            break;
        case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
        {
            ret_code_t ret;
            do
            {
				process_packet(m_rx_buffer[m_active_buffer]);

                ret = app_usbd_cdc_acm_read(&m_app_cdc_acm,
                                            m_rx_buffer[m_active_buffer],
                                            READ_SIZE);
                m_active_buffer = m_active_buffer ? 0:1;
                NRF_LOG_INFO("frame receive");

            } while (ret == NRF_SUCCESS);
            int idx=0;
            flag=0;
            flag = receive_packet(idx);

            bsp_board_led_invert(LED_CDC_ACM_RX);
            break;
        }
        default:
            break;
    }
}

static void usbd_user_ev_handler(app_usbd_event_type_t event)
{
    switch (event)
    {
        case APP_USBD_EVT_DRV_SUSPEND:
            bsp_board_led_off(LED_USB_RESUME);
            break;
        case APP_USBD_EVT_DRV_RESUME:
            bsp_board_led_on(LED_USB_RESUME);
            break;
        case APP_USBD_EVT_STARTED:
            break;
        case APP_USBD_EVT_STOPPED:
            app_usbd_disable();
            bsp_board_leds_off();
            break;
        case APP_USBD_EVT_POWER_DETECTED:
            NRF_LOG_INFO("USB power detected");

            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }
            break;
        case APP_USBD_EVT_POWER_REMOVED:
            NRF_LOG_INFO("USB power removed");
            app_usbd_stop();
            break;
        case APP_USBD_EVT_POWER_READY:
            NRF_LOG_INFO("USB ready");
            app_usbd_start();
            break;
        default:
            break;
    }
}

static void bsp_event_callback(bsp_event_t ev)
{
    ret_code_t ret;
    switch ((unsigned int)ev)
    {
        case CONCAT_2(BSP_EVENT_KEY_, BTN_CDC_DATA_SEND):
        {
            m_send_flag = 1;
            break;
        }
        
        case BTN_CDC_DATA_KEY_RELEASE :
        {
            m_send_flag = 0;
            break;
        }

        case CONCAT_2(BSP_EVENT_KEY_, BTN_CDC_NOTIFY_SEND):
        {
            ret = app_usbd_cdc_acm_serial_state_notify(&m_app_cdc_acm,
                                                       APP_USBD_CDC_ACM_SERIAL_STATE_BREAK,
                                                       false);
            UNUSED_VARIABLE(ret);
            break;
        }

        default:
            return; // no implementation needed
    }
}

static void init_bsp(void)
{
    ret_code_t ret;
    ret = bsp_init(BSP_INIT_BUTTONS, bsp_event_callback);
    APP_ERROR_CHECK(ret);
    
    UNUSED_RETURN_VALUE(bsp_event_to_button_action_assign(BTN_CDC_DATA_SEND,
                                                          BSP_BUTTON_ACTION_RELEASE,
                                                          BTN_CDC_DATA_KEY_RELEASE));
    
    /* Configure LEDs */
    bsp_board_init(BSP_INIT_LEDS);
}

static void init_cli(void)
{
    ret_code_t ret;
    ret = bsp_cli_init(bsp_event_callback);
    APP_ERROR_CHECK(ret);
    nrf_drv_uart_config_t uart_config = NRF_DRV_UART_DEFAULT_CONFIG;
    uart_config.pseltxd = TX_PIN_NUMBER;
    uart_config.pselrxd = RX_PIN_NUMBER;
    uart_config.hwfc    = NRF_UART_HWFC_DISABLED;
    ret = nrf_cli_init(&m_cli_uart, &uart_config, true, false, NRF_LOG_SEVERITY_INFO);
    APP_ERROR_CHECK(ret);
    ret = nrf_cli_start(&m_cli_uart);
    APP_ERROR_CHECK(ret);
}




int main(void)
{
    ret_code_t ret;
	ringbuf_init (&eegRing, ringBuffer, RINGBUF_SIZE);
	uint8_t idx=0;
	uint8_t p = 0;
	//uint8_t VREF = 5;
	//uint8_t debugBuff [EEG_FRAME_SIZE] = {0};
	uint32_t val = 0;
	double res[proc_frame] = {0};
	double feature_vec[fea_vec_frame] = {0};

	double *p_fea = 0;
	int temp=0;
	int32_t i = 0;
	int k = 0;
	//int N_coe = 23;
//	double coe[23]={-0.00721228495268340,0.00694879918830175,	0.0315716518132703,	0.0550962141511825,
//			0.0509946868303976,	0.00753853972032553,	-0.0502781439611508,-0.0682091000322473,-0.00291397395931581,
//			0.135156077398719,0.276340313183522,	0.335993883039056,0.276340313183522,0.135156077398719,
//			-0.00291397395931581,-0.0682091000322473,-0.0502781439611508,	0.00753853972032553,	0.0509946868303976,
//			0.0550962141511825,	0.0315716518132703,	0.00694879918830175,	-0.00721228495268340};

	// for version 0 use
	int j = 0;
	int32_t b[6] = {0};
	uint32_t c[6] = {0};
	char feature_vec_tx[fea_vec_frame*3] = {0};



    static const app_usbd_config_t usbd_config = {
        .ev_state_proc = usbd_user_ev_handler
    };
    //cdc_acm_user_ev_handler

    ret = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(ret);
	NRF_LOG_DEFAULT_BACKENDS_INIT();

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
    
    nrf_drv_clock_lfclk_request(NULL);

    while(!nrf_drv_clock_lfclk_is_running())
    {
        /* Just waiting */
    }

    ret = app_timer_init();
    APP_ERROR_CHECK(ret);

    init_bsp();
    init_cli();


    app_usbd_serial_num_generate();

    ret = app_usbd_init(&usbd_config);
    APP_ERROR_CHECK(ret);
    NRF_LOG_INFO("USBD CDC ACM example started.");


    app_usbd_class_inst_t const * class_cdc_acm = app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm);
    ret = app_usbd_class_append(class_cdc_acm);
    APP_ERROR_CHECK(ret);

    if (USBD_POWER_DETECTION)
    {
        ret = app_usbd_power_events_enable();
        APP_ERROR_CHECK(ret);
    }
    else
    {
        NRF_LOG_INFO("No USB power detection enabled\r\nStarting USB now");

        app_usbd_enable();
        app_usbd_start();
    }

    while (true)
    {
        while (app_usbd_event_queue_process())
        {
            /* Nothing to do */
        }
        
        if(m_send_flag) //triggered by button press
        {
            static int  frame_counter;

            size_t size = sprintf(m_tx_buffer, "Hello USB CDC FA demo: %u\r\n", frame_counter); // example for writing text and data to a buffer

            ret = app_usbd_cdc_acm_write(&m_app_cdc_acm, m_tx_buffer, size); //sending the buffer out over usb cdc
            if (ret == NRF_SUCCESS)
            {
                ++frame_counter;
            }
        }
        
        nrf_cli_process(&m_cli_uart);

        ///////////////////////////////////////////////////////////////////////
        // TODO Process the data here
        // I've assumed you want to read in all the samples into a buffer and then process it
        // but feel free to change this. 27 is the number of bytes in one sample.
        ///////////////////////////////////////////////////////////////////////
        k=0;
        if(flag==1){
        	while(k<8){
        		res[i] = tem[k];
        		k += 1;
        		i += 1;
        	}
        	flag=2;
        }
        if(i==400){
    		p_fea = time_domain(res, feature_vec);
    		p_fea = freq_domain(res,200, feature_vec);
    		memset(res,0,sizeof(double)*proc_frame);
    		i=0;
    		for (j=0;j<6;j++){
    			feature_vec[j] = feature_vec[j] * 12 * pow(2, 24) / (2 * VREF);
    			b[j] = (int32_t) feature_vec[j];
    			c[j] = (uint32_t) b[j];
    			feature_vec_tx[(j % 6)*3] =(c[j] >> 24) % 256;
    			feature_vec_tx[(j % 6)*3+1] =(c[j] >> 16) % 256;
    			feature_vec_tx[(j % 6)*3+2] =(c[j] >> 8) % 256;
    		}
    		ret = app_usbd_cdc_acm_write(&m_app_cdc_acm, feature_vec_tx, 18);
    		temp=temp+1;
        }
//        if(temp == 3){
//        	while(1){
//        	}
//        }

        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
        /* Sleep CPU only if there was no interrupt since last loop processing */
        __WFE();
    }
}

/** @} */
