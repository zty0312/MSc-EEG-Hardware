load('S1_filtered_EarEEG.mat');
x=10^6*cleaned_input(1:6000,1);
figure(1)
plot(x);
hold on;
for i=1:60
    plot([100*i 100*i], get(gca, 'YLim'), '-r', 'LineWidth', 0.5);
    hold on;
end
title("One epoch EEG signal with the sliding window (\lambda=100)");
xlabel("sample",'fontsize',12);
ylabel("Amplitude (\muV)",'fontsize',12);

x1=x(1:500,1);
figure(2)
plot(x1);
hold on;
for i=1:5
    plot([100*i 100*i], get(gca, 'YLim'), '-r', 'LineWidth', 0.5);
    hold on;
    p=x1((i-1)*100+1:i*100,1);
    [max_val,max_idx]=max(p);
    [min_val,min_idx]=min(p);
    max_idx=(i-1)*100+max_idx;
    min_idx=(i-1)*100+min_idx;
    plot(max_idx,max_val,'oblack');
    hold on;
    plot(min_idx,min_val,'oblack');
    hold on;
    plot([min_idx max_idx],[min_val max_val],'black','LineWidth', 1);
    hold on;
end
title("Applying MMD on EEG sub-band");
xlabel("sample",'fontsize',12);
ylabel("Amplitude (\muV)",'fontsize',12);