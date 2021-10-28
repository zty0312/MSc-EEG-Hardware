clear 
clc
load('S1_filtered_EarEEG.mat');
input_train=input_data(:,1);
load('S1_filtered_ScalpEEG.mat');
Hyp=hypnogram;
load('S2_filtered_EarEEG.mat');
input=input_data(:,1);
input_train=[input_train;input];
load('S2_filtered_ScalpEEG.mat');
Hyp=[Hyp;hypnogram];
n=length(Hyp);
fs=200;
epochLength = 6000;
[feature_vec,tot_fea]=feature_extraction_total(input_train,100,n,epochLength,fs);
% feature_vec=feature_vec-ones(n,1)*mean(feature_vec,"omitnan");
% feature_vec=feature_vec./range(feature_vec);
Hypnogram=cell(n,1);
k1=0;k2=0;k3=0;k4=0;
for i=1:n
    switch (Hyp(i))
        case 0
            Hypnogram(i)={'W'};          
            k1=k1+1;
        case 1
            Hypnogram(i)={'N1'};
            k2=k2+1;
        case 2
            Hypnogram(i)={'N2'};
            k3=k3+1;
        case 3
            Hypnogram(i)={'N3'};
            k4=k4+1;
    end      
end
S = feature_vec(:,1);K = feature_vec(:,2);MMD = feature_vec(:,3); 
numZeroCross = feature_vec(:,4);Activity= feature_vec(:,5); Mobility=feature_vec(:,6);
Complexity =feature_vec(:,7);Ren_en=feature_vec(:,8);per_power_delta=feature_vec(:,9);
per_power_theta=feature_vec(:,10); per_power_alpha=feature_vec(:,11); 
per_power_beta=feature_vec(:,12);per_power_gamma=feature_vec(:,13);freq_med=feature_vec(:,14);
fea_T=table(S,K,MMD,numZeroCross,Activity,Mobility,Complexity,Ren_en,per_power_delta,per_power_theta,per_power_alpha,per_power_beta,per_power_gamma,freq_med,Hypnogram);
fea_T.Hypnogram = categorical(fea_T.Hypnogram);
[idx,scores] = fscmrmr(fea_T,'Hypnogram');
bar(scores(idx))
xlabel('Feature rank')
ylabel('Feature importance score')
xticklabels([6,10,2,11,4,8,13,9,12,7,5,1,3,14]);
title('mRMR selection');