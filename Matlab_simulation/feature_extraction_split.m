function feature_vec=feature_extraction_split(cleaned_input,n,epochLength,fs,Hyp)
feature_vec=zeros(n,7);
feature_vec_sub=zeros(15,6);
p=15; %subepochlength
ptot=0;
numZeroCross=0;
pband_theta=0;pband_alpha=0;pband_gamma=0;
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
         numZeroCross = numZeroCross+ double(num);        
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
         ptot = ptot+bandpower(x_in,fs,[0 fs/2]);   
         pband_theta = pband_theta + bandpower(x_in,fs,[4 8]); 
         pband_alpha = pband_alpha + bandpower(x_in,fs,[8 12]); 
         pband_gamma = pband_gamma + bandpower(x_in,fs,[30 50]); 

%          per_power_theta = 100*(pband_theta/ptot); 
%          per_power_alpha = 100*(pband_alpha/ptot); 
%          per_power_gamma = 100*(pband_gamma/ptot);    
         toc
         feature_vec_sub(k,1:3)=[K,Mobility,numZeroCross];
         %feature_vec_sub(k,:)=[K,Mobility,numZeroCross,per_power_theta,per_power_alpha,per_power_gamma];
     end
     per_power_theta = 100*(pband_theta/ptot); 
     per_power_alpha = 100*(pband_alpha/ptot); 
     per_power_gamma = 100*(pband_gamma/ptot); 
     numZeroCross = feature_vec_sub(15,3); 
%     K=kurtosis(feature_vec_sub(:,1));
%      feature_vec(i,:)=weight*feature_vec_sub;
     feature_mean=mean(feature_vec_sub,"omitnan");
     feature_vec(i,1:3)=feature_mean(:,1:3);
     feature_vec(i,3)=numZeroCross;
     %feature_vec(i,1)=K;
     feature_vec(i,4:6)=[per_power_theta,per_power_alpha,per_power_gamma];
     numZeroCross=0;
     pband_theta=0;pband_alpha=0;pband_gamma=0;ptot=0;
end
feature_vec(:,7) = Hyp;
% fea_T.Hypnogram = categorical(fea_T.Hypnogram);
   
end