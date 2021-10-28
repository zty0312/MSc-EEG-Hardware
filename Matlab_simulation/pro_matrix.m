clear 
clc
load('fea_T.mat');
load('S1_filtered_EarEEG.mat');
input_train=input_data(:,1);
load('S1_filtered_ScalpEEG.mat');
Hyp=hypnogram;
load('S2_filtered_EarEEG.mat');
input=input_data(:,1);
input_train=[input_train;input];
load('S2_filtered_ScalpEEG.mat');
Hyp=[Hyp;hypnogram];
n0=length(Hyp);
fs=200;
epochLength = 6000;
feature_vec_30s=feature_extraction_split(input_train,n0,epochLength,fs,Hyp);
save feature_vec_30s
% %% T=1s
% epochLength = 200;
% res=[];
% for i=1:n0
%     k=ones(30,1);
%     Hyp_tem=kron(k,Hyp(i));
%     res=[res;Hyp_tem];
% end
% Hyp_1=res;
% n=length(Hyp_1);
% feature_vec_1s=feature_extraction(input_train,n,epochLength,fs,Hyp_1);
% label_pre=Hyp(2:end);
% Hyp=[Hyp;label_pre];
% fea_pre=zeros(179,7);
% for i=2:n0
%     fea_pre(i-1,:)=feature_vec_1s(30*(i-1)+1,:);
% end
% feature_vec=[feature_vec_30s;fea_pre];
% feature_vec(:,7)=Hyp;

%% T=2s
epochLength = 400;
res=[];
for i=1:n0
    k=ones(15,1);
    Hyp_tem=kron(k,Hyp(i));
    res=[res;Hyp_tem];
end
Hyp_2=res;
n=length(Hyp_2);
feature_vec_2s=feature_extraction(input_train,n,epochLength,fs,Hyp_2);

label_pre=Hyp(2:end);
Hyp=[Hyp;label_pre];
fea_pre=zeros(179,7);
for i=2:n0
    fea_pre(i-1,:)=feature_vec_2s(15*(i-1)+1,:);
end
feature_vec=[feature_vec_30s;fea_pre];
feature_vec(:,7)=Hyp;

% %% T=3s
% epochLength = 600;
% res=[];
% for i=1:n0
%     k=ones(10,1);
%     Hyp_tem=kron(k,Hyp(i));
%     res=[res;Hyp_tem];
% end
% Hyp_3=res;
% n=length(Hyp_3);
% feature_vec_3s=feature_extraction(input_train,n,epochLength,fs,Hyp_3);
% 
% label_pre=Hyp(2:end);
% Hyp=[Hyp;label_pre];
% fea_pre=zeros(179,7);
% for i=2:n0
%     fea_pre(i-1,:)=feature_vec_3s(10*(i-1)+1,:);
% end
% feature_vec=[feature_vec_30s;fea_pre];
% feature_vec(:,7)=Hyp;

% %% T=5s
% epochLength = 1000;
% res=[];
% for i=1:n0
%     k=ones(6,1);
%     Hyp_tem=kron(k,Hyp(i));
%     res=[res;Hyp_tem];
% end
% Hyp_5=res;
% n=length(Hyp_5);
% feature_vec_5s=feature_extraction(input_train,n,epochLength,fs,Hyp_5);
% label_pre=Hyp(2:end);
% Hyp=[Hyp;label_pre];
% fea_pre=zeros(179,7);
% for i=2:n0
%     fea_pre(i-1,:)=feature_vec_5s(6*(i-1)+1,:);
% end
% feature_vec=[feature_vec_30s;fea_pre];
% feature_vec(:,7)=Hyp;

% %% T=6s
% epochLength = 1200;
% res=[];
% for i=1:n0
%     k=ones(5,1);
%     Hyp_tem=kron(k,Hyp(i));
%     res=[res;Hyp_tem];
% end
% Hyp_6=res;
% n=length(Hyp_6);
% feature_vec_6s=feature_extraction(input_train,n,epochLength,fs,Hyp_6);
% label_pre=Hyp(2:end);
% Hyp=[Hyp;label_pre];
% fea_pre=zeros(179,7);
% for i=2:n0
%     fea_pre(i-1,:)=feature_vec_6s(5*(i-1)+1,:);
% end
% feature_vec=[feature_vec_30s;fea_pre];
% feature_vec(:,7)=Hyp;

% %% T=10s
% epochLength = 2000;
% res=[];
% for i=1:n0
%     k=ones(3,1);
%     Hyp_tem=kron(k,Hyp(i));
%     res=[res;Hyp_tem];
% end
% Hyp_10=res;
% n=length(Hyp_10);
% feature_vec_10s=feature_extraction(input_train,n,epochLength,fs,Hyp_10);
% label_pre=Hyp(2:end);
% Hyp=[Hyp;label_pre];
% fea_pre=zeros(179,7);
% for i=2:n0
%     fea_pre(i-1,:)=feature_vec_10s(3*(i-1)+1,:);
% end
% feature_vec=[feature_vec_30s;fea_pre];
% feature_vec(:,7)=Hyp;

% %% T=15s
% epochLength = 3000;
% res=[];
% for i=1:n0
%     k=ones(2,1);
%     Hyp_tem=kron(k,Hyp(i));
%     res=[res;Hyp_tem];
% end
% Hyp_15=res;
% n=length(Hyp_15);
% feature_vec_15s=feature_extraction(input_train,n,epochLength,fs,Hyp_15);
% label_pre=Hyp(2:end);
% Hyp=[Hyp;label_pre];
% fea_pre=zeros(179,7);
% for i=2:n0
%     fea_pre(i-1,:)=feature_vec_15s(2*(i-1)+1,:);
% end
% feature_vec=[feature_vec_30s;fea_pre];
% feature_vec(:,7)=Hyp;
% 
% %% same scheme for pre
%  [fit_30s,prob,~]=trainedModel.predictFcn(feature_vec_30s(:,1:6));
%  label_pre=fit_30s(1:end-1);
%  prob=-1./prob;
%  prob(isinf(prob))=10000;
%  prob_m=normalize(prob,'range');
%  for i=2:n0
%      k=label_pre(i-1);
%      trans_prob(i,:)=tran_mat(k+1,:);
%      final_prob(i,:)=trans_prob(i,:).*prob_m(i,:);
%  end
%  [final,idx]=max(final_prob,[],2);
%  idx=idx-1;
%  idx(1)=fit_30s(1);
%  true_pred=(idx==Hyp(1:180,1));
%  true_num=sum(true_pred==1);
%  acc=true_num/180;
% %  confusionchart(Hyp(1:180,1),idx)
% %  title('Confusion Matrix')
%  figure (2)
%  subplot(2,1,1)
%  plot(Hyp(1:180,1));
%  hold on
%  title('Manual Hypnogram')
%  xlabel('Epoch');
%  ylabel('Sleep Stage');
%  subplot(2,1,2)
%  plot(idx);
%  title('Predicted Hypnogram')
%  xlabel('Epoch');
%  ylabel('Sleep Stage');
%  hold on
%  for i=1:180
%      if(true_pred(i)==0)
%          subplot(2,1,1)
%          plot(i,Hyp(i),'r.');
%          subplot(2,1,2)
%          plot(i,idx(i),'r.');
%      end
%  end
% 
% LOSS=loss(trainedModel.ClassificationSVM,feature_vec_30s(:,1:6),Hyp(1:180,1));
save feature_vec