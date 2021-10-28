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

feature_vec=feature_vec-ones(n,1)*mean(feature_vec,"omitnan");
feature_vec=feature_vec./range(feature_vec);

S = feature_vec(:,1);K =feature_vec(:,2);MMD = feature_vec(:,3); 
numZeroCross = feature_vec(:,4);Activity= feature_vec(:,5); Mobility=feature_vec(:,6);
Complexity =feature_vec(:,7);Ren_en=feature_vec(:,8);per_power_delta=feature_vec(:,9);
per_power_theta=feature_vec(:,10); per_power_alpha=feature_vec(:,11); 
per_power_beta=feature_vec(:,12);per_power_gamma=feature_vec(:,13);freq_med=feature_vec(:,14);

feature_time=feature_vec(:,1:8);
feature_fre=feature_vec(:,9:14);
[pcs_t,pcaData_t,~,~,pexp_t] = pca(feature_time);
[pcs_f,pcaData_f,~,~,pexp_f] = pca(feature_fre);
% figure (1)
% pareto(pexp_t);
% xlabel('PCA features');
% ylabel('percentage of total variance');
% hold on;
% title("PCA in time-domain features");
% figure (2)
% pareto(pexp_f);
% hold on;
% xlabel('PCA features');
% ylabel('percentage of total variance');
% hold on;
% title("PCA in frequency-domain frequency");
k1=0;k2=0;k3=0;k4=0;
Hypnogram=cell(n,1);
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
fea_T = table(S,K,MMD,numZeroCross,Activity,Mobility,Complexity,Ren_en,per_power_delta,per_power_theta,per_power_alpha,per_power_beta,per_power_gamma,freq_med,Hypnogram);
fea_T.Hypnogram = categorical(fea_T.Hypnogram);
fea_pca_tf_T=table(pcaData_t(:,1),pcaData_t(:,2),pcaData_t(:,3),pcaData_t(:,4),pcaData_f(:,1),pcaData_f(:,2),pcaData_f(:,3),Hypnogram);


% idx_0=(Hyp==0);
% idx_1=(Hyp==1);
% idx_2=(Hyp==2);
% idx_3=(Hyp==3);
% figure (3)
% 
% subplot(2,4,1)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,2),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,2),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,2),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,2),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 2');
% 
% subplot(2,4,2)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,3),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,3),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,2),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,3),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 3');
% 
% subplot(2,4,3)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,4),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,4),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,4),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,4),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 4');
% 
% subplot(2,4,4)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,5),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,5),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,5),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,5),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 5');
% 
% subplot(2,4,5)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,6),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,6),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,6),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,6),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 6');
% 
% 
% subplot(2,4,6)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,7),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,7),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,7),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,7),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 7');
% 
% subplot(2,4,7)
% plot(feature_vec(idx_0,1),feature_vec(idx_0,8),'r.','MarkerSize',12);
% hold on;    
% plot(feature_vec(idx_1,1),feature_vec(idx_1,8),'g.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_2,1),feature_vec(idx_2,8),'b.','MarkerSize',12);
% hold on;
% plot(feature_vec(idx_3,1),feature_vec(idx_3,8),'y.','MarkerSize',12);
% hold on;
% xlabel('feature 1');
% ylabel('feature 8');
% hold on;