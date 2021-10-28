load('fea_T.mat');

Pm=[0,1,2,3];
Pc=[0,1,2,3];

[m,n]=meshgrid(1:5);
surf(m,n,0*m,tran_mat,'linestyle',':');
%%%%%%%%%自定义颜色%%%%%%%%%%%
colorbar;
%%%%%%%%%%%%%%%%%%%%%%%%%%
view(2);axis ij
axis([1,5,1,5])
set(gca,'xtick',1.5:4.5,'xticklabel',Pm,'ytick',1.5:4.5,'yticklabel',Pc)
[m,n]=meshgrid(1.5:4.5);
%%%%%%%%显示百分比%%%%%%%%%%%%
text(m(:),n(:),cellfun(@(x)(num2str(x)),num2cell(tran_mat),'UniformOutput',false),'HorizontalAlignment','center','color','b')
xlabel('Current Stage'),ylabel('Previous Stage');

