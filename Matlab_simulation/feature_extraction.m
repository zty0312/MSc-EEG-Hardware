function feature_vec=feature_extraction(cleaned_input,n,epochLength,fs,Hyp)
feature_vec=zeros(n,7);
for i=1:n
    %% feature extraction for Left-Ear-1
     x_data=cleaned_input((i-1)*epochLength+1:i*epochLength);
    %% Time Domain
    %standard statistics  (2 features)
    tic
    K=kurtosis(x_data); %Kurtosis
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
    %% Frequency Domain
    %Spectral Power in Frequency Bands (5 features)
    tic
    ptot = bandpower(x_data,fs,[0 fs/2]);   
    pband_theta = bandpower(x_data,fs,[4 8]); 
    pband_alpha = bandpower(x_data,fs,[8 12]); 
    pband_gamma = bandpower(x_data,fs,[30 50]); 

    per_power_theta = 100*(pband_theta/ptot); 
    per_power_alpha = 100*(pband_alpha/ptot);
    per_power_gamma = 100*(pband_gamma/ptot);    
    toc
    %% feature selection for Left-Ear-1
    feature_vec(i,1:6)=[K,Mobility,numZeroCross,per_power_theta,per_power_alpha,per_power_gamma];   
end
feature_vec(:,7) = Hyp;