clear 
clc
load('S1_filtered_EarEEG.mat');
input_train=input_data(:,1);
load('S1_filtered_ScalpEEG.mat');
Hyp=hypnogram;
% load('S2_filtered_EarEEG.mat');
% input=input_data(:,1);
% input_train=[input_train;input];
% load('S2_filtered_ScalpEEG.mat');
% Hyp=[Hyp;hypnogram];
n=length(Hyp);
fs=200;
epochLength = 6000;
[feature_vec,tot_fea]=feature_extraction_total(input_train,100,n,epochLength,fs);
Hypnogram=cell(n,1);
k1=1;k2=1;k3=1;k4=1;
fea_grp_0=zeros(1,14);
fea_grp_1=zeros(1,14);
fea_grp_2=zeros(1,14);
fea_grp_3=zeros(1,14);
feature_vec_nor=feature_vec-ones(n,1)*mean(feature_vec,"omitnan");
feature_vec_nor=feature_vec_nor./range(feature_vec_nor);
for i=1:n
    switch (Hyp(i))
        case 0
            Hypnogram(i)={'W'};
            fea_grp_0(k1,:)=feature_vec_nor(i,:);
            k1=k1+1;
        case 1
            Hypnogram(i)={'N1'};
            fea_grp_1(k2,:)=feature_vec_nor(i,:);
            k2=k2+1;
        case 2
            Hypnogram(i)={'N2'};
            fea_grp_2(k3,:)=feature_vec_nor(i,:);
            k3=k3+1;
        case 3
            Hypnogram(i)={'N3'};
            fea_grp_3(k4,:)=feature_vec_nor(i,:);
            k4=k4+1;
    end      
end

if k1==1
   mean_fea_grp_0=zeros(1,tot_fea);
else
   mean_fea_grp_0= mean(fea_grp_0);
end
if k2==1
   mean_fea_grp_1=zeros(1,tot_fea);
else
   mean_fea_grp_1= mean(fea_grp_1);
end
if k3==1
   mean_fea_grp_2=zeros(1,tot_fea);
else
   mean_fea_grp_2= mean(fea_grp_2);
end
if k4==1
   mean_fea_grp_3=zeros(1,tot_fea);
else
   mean_fea_grp_3= mean(fea_grp_3);
end
%parallelcoords(feature_vec_nor,"Group",Hypnogram);
figure (1)
grp_mean=[mean_fea_grp_0;mean_fea_grp_1;mean_fea_grp_2];
parallelcoords(grp_mean,"Group",0:2);

xline(4,'-.r', 'LineWidth', 2);
xline(6,'-.r', 'LineWidth', 2);
xline(11,'-.r', 'LineWidth', 2);
xline(13,'-.r', 'LineWidth', 2);



title("Difference of W,N1,N2 at 14 features");
xlabel("feature",'fontsize',12);
ylabel("Mean value",'fontsize',12);
