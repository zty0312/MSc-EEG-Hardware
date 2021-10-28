clear
clc
%% Load Data
load('S1_filtered_EarEEG.mat');
input_train=input_data(:,1);
load('S1_filtered_ScalpEEG.mat');
Hyp=hypnogram;
load('S2_filtered_EarEEG.mat');
input=input_data(:,1);
input_train=[input_train;input];
load('S2_filtered_ScalpEEG.mat');
Hyp=[Hyp;hypnogram];
% load('S3_filtered_EarEEG.mat');
% input=input_data(:,1);
% input_train=[input_train;input];
% load('S3_filtered_ScalpEEG.mat');
% Hyp=[Hyp;hypnogram];
% load('S4_filtered_EarEEG.mat');
% input=input_data(:,1);
% input_train=[input_train;input];
% load('S4_filtered_ScalpEEG.mat');
% Hyp=[Hyp;hypnogram];


nfea=6;
epochLength=6000;
fs=200;
n_input=length(Hyp);

% input_train=filterData(input_train);
[fea_T,feature_vec,tran_mat,feature_pre_contain]=feature_extraction_split(input_train,n_input,epochLength,fs,Hyp);
save fea_T;
% saveLearnerForCoder(trainedModel.ClassificationSVM,'ClassificationLearnerModel')
