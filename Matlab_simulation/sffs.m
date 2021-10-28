function [Selected_Features,Performance_Features]=sffs(data,label)
S = [];
W = [];
P=[];
Totalbestval = 0;
loop=1;
while loop>0
    bestval=0;
    bestidx=0;
    correct_val=0;        
    for i1=1:size(data,2)
        if ~ismember(i1,S)
            cp=classperf(label);
                for i = 1:10
                    cvind = crossvalind('Kfold',label,10);
                    test = (cvind == i); train = ~test;
                    if isempty(S)
                        data2=data(:,i1);
                        class = classify(data2(test,:),data2(train,:),label(train,:),'diagQuadratic');
                        classperf(cp,class,test);
                    else
                    data2=[data(:,S) data(:,i1)]; 
                    class = classify(data2(test,:),data2(train,:),label(train,:));
                    classperf(cp,class,test);
                    end
                end
                Correct_rate=cp.CorrectRate;
                Error_rate=cp.ErrorRate;
                if Correct_rate>correct_val
                    bestval = Error_rate;
                    correct_val=Correct_rate;
                    bestidx = i1;
                end
      
                
        end
    end
    if correct_val - Totalbestval<=0.01
        break;
    else
        S = [S bestidx];
        W = [W bestval];
        P= [P correct_val];
        loop=loop+1;
        Totalbestval=correct_val;
    end
end
Selected_Features=S;
Performance_Features=P;%(length(P));
bar(S,P);
xlabel("feature combination");
ylabel("accuracy");
%xticklabels(strrep(T.Properties.VariableNames(idx),'_','\_'))
end