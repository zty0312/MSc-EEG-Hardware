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
[feature_vec,fea_potential_time,total_time]=feature_extraction_time(input_train,100,n,epochLength,fs);
tic
[pcs,pcaData,~,~,pexp] = pca(feature_vec);
t_pca=total_time+toc;
t_plot=[fea_potential_time,t_pca];
bar(t_plot);
for i = 1:length(t_plot)
    text(i,t_plot(i),num2str(t_plot(i)),'HorizontalAlignment','center', 'VerticalAlignment','bottom');
end

ylabel('time(s)');
set(gca,'xticklabel',{'K','numZeroCross','Mobility','Alpha band power','Complexity','Theta band power','PCA features'});
xtickangle(45);
title('Computation time');