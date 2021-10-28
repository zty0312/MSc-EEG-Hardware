function acc=measure_prob(trainedModel,fea_pre,feature_vec_30s,Hyp,n0,tran_mat)
 fit_pre=trainedModel.predictFcn(fea_pre(:,1:6));
 [fit_30s,prob,~]=trainedModel.predictFcn(feature_vec_30s(:,1:6));
 
 prob=-1./prob;
 prob(isinf(prob))=10000;
 prob_m=normalize(prob,'range');
 for i=2:n0
     k=fit_pre(i-1);
     trans_prob(i,:)=tran_mat(k+1,:);
     final_prob(i,:)=trans_prob(i,:).*prob_m(i,:);
 end
 [final,idx]=max(final_prob,[],2);
 idx=idx-1;
 idx(1)=fit_30s(1);
 true_pred=(idx==Hyp(1:180,1));
 true_num=sum(true_pred==1);
 acc=true_num/180;
%  figure (1)
%  confusionchart(Hyp(1:180,1),idx)
%  title('Confusion Matrix(15s pre)')
 figure (2)
 subplot(2,1,1)
 plot(Hyp(1:180,1));
 hold on
 title('Manual Hypnogram')
 xlabel('Epoch');
 ylabel('Sleep Stage');
 subplot(2,1,2)
 plot(idx);
 title('Predicted Hypnogram(15s pre)')
 xlabel('Epoch');
 ylabel('Sleep Stage');
 hold on
 for i=1:180
     if(true_pred(i)==0)
         subplot(2,1,1)
         plot(i,Hyp(i),'r.');
         subplot(2,1,2)
         plot(i,idx(i),'r.');
     end
 end

 
 