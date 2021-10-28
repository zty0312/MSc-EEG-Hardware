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
feature_vec_30s=feature_extraction(input_train,n,epochLength,fs,Hyp);
feature_vec_2s=feature_extraction_split(input_train,n,epochLength,fs,Hyp);
% feature_vec_2s_mean=feature_extraction_mean(input_train,n,epochLength,fs,Hyp);
feature_vec_2s_weighted=feature_extraction_weighted(input_train,n,epochLength,fs,Hyp);