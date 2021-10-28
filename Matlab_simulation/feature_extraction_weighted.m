function feature_vec=feature_extraction_weighted(cleaned_input,n,epochLength,fs,Hyp)
feature_vec=zeros(n,7);
feature_vec_sub=zeros(15,6);
p=15; %subepochlength
miu=8;sigma=6;
idx=1:0.5:15;
weight=(1/((sqrt(2*pi))*sigma))*exp(-((idx-miu).^2)/(2*sigma.^2));
weight=weight(1:2:end);
for i=1:n
    %% feature extraction for Left-Ear-1
     x_data=cleaned_input((i-1)*epochLength+1:i*epochLength);
     for k=1:p
         x_in=x_data((k-1)*epochLength/p+1:k*epochLength/p);
        %standard statistics  (2 features)
         tic
         K=kurtosis(x_in); %Kurtosis
         toc
         %zero crossing (1 features)
         tic
         zcd = dsp.ZeroCrossingDetector;
         num=zcd(x_in);
         numZeroCross = double(num);        
         toc
         %Hjorth parameters (3 features)
         tic
         Activity=var(x_in);
         toc
         tic
         dx_l1= gradient(x_in);
         Mobility=sqrt(var(dx_l1)/Activity);
         toc
         tic
         ptot = bandpower(x_in,fs,[0 fs/2]);   
         pband_theta = bandpower(x_in,fs,[4 8]); 
         pband_alpha = bandpower(x_in,fs,[8 12]); 
         pband_gamma = bandpower(x_in,fs,[30 50]); 

         per_power_theta = 100*(pband_theta/ptot); 
         per_power_alpha = 100*(pband_alpha/ptot); 
         per_power_gamma = 100*(pband_gamma/ptot);    
         toc
         feature_vec_sub(k,:)=[K,Mobility,numZeroCross,per_power_theta,per_power_alpha,per_power_gamma];
     end
     feature_weighted=weight*feature_vec_sub;
     feature_weighted_mean=feature_weighted;
     feature_vec(i,1:6)=feature_weighted_mean;
end
feature_vec(:,7) = Hyp;
% fea_T.Hypnogram = categorical(fea_T.Hypnogram);
   
end