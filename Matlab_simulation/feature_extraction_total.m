function [feature_vec,tot_fea]=feature_extraction_total(cleaned_input,lambda,n,epochLength,fs)
feature_vec=zeros(n,14);
for i=1:n
    %% feature extraction for Left-Ear-1
     x_data=cleaned_input((i-1)*epochLength+1:i*epochLength);
    %% Time Domain
    %standard statistics  (2 features)
    tic
    S=skewness(x_data); %Skewness
    K=kurtosis(x_data); %Kurtosis
    toc
    %maximum-minimum distance (1 features)
    tic
    x_MA=zeros(lambda,epochLength/lambda);
    for k=1:epochLength/lambda
        x_MA(:,k)=x_data((k-1)*lambda+1:k*lambda,1);     
    end
    [x_max,i_max]= max(x_MA);
    [x_min,i_min]=min(x_MA);
    delt_y=(x_max-x_min);
    delt_x=(i_max-i_min);
    d=sqrt(delt_x.^2+delt_y.^2);
    MMD=sum(abs(d));
    toc
    %zero crossing (1 features)
    tic
    zcd = dsp.ZeroCrossingDetector;
    num=zcd(x_data);
    numZeroCross = double(num);
    toc
    %Hjorth parameters (3 features)
    tic
    Activity=var(x_data);
    toc
    tic
    dx_l1= gradient(x_data);
    Mobility=sqrt(var(dx_l1)/Activity);
    toc
    tic
    ddx_l1=gradient(dx_l1);
    Complexity=sqrt(var(ddx_l1)*Activity/var(dx_l1)^2);
    toc
    %Renyi entropy (1 features)
    tic
    q=2;
    [N,edges] = histcounts(x_data);
    p=N./epochLength;
    Ren_en=(1/1-q)*log(sum(p.^q));
    toc
    %% Frequency Domain
    %Spectral Power in Frequency Bands (5 features)
    tic
    ptot = bandpower(x_data,fs,[0 fs/2]);   
    pband_delta = bandpower(x_data,fs,[0 4]); 
    pband_theta = bandpower(x_data,fs,[4 8]); 
    pband_alpha = bandpower(x_data,fs,[8 12]); 
    pband_beta = bandpower(x_data,fs,[12 30]); 
    pband_gamma = bandpower(x_data,fs,[30 100]); 

    per_power_delta = 100*(pband_delta/ptot);
    per_power_theta = 100*(pband_theta/ptot); 
    per_power_alpha = 100*(pband_alpha/ptot);
    per_power_beta = 100*(pband_beta/ptot); 
    per_power_gamma = 100*(pband_gamma/ptot);    
    toc
    %Median Frequency 
    tic
    freq_med = medfreq(x_data);
    toc
    %% feature selection for Left-Ear-1
    feature_vec(i,:)=[S,K,MMD,numZeroCross,Activity,Mobility,Complexity,Ren_en,per_power_delta,per_power_theta,per_power_alpha,per_power_beta,per_power_gamma,freq_med];
    tot_fea=size(feature_vec,2);
    

end