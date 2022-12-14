close all
clear all

global beta deltaS deltaI eta A num tau deltaw omega kappa st_host;
num=1000;
u0 = load('../../data/init_node.txt')'; %ノードが各状態をとる確率(転置)(非対策脆弱、非対策感染、非対策回復、対策脆弱、対策感染、対策保護)
A=load('../../data/cmp_adj_mrx.txt');%ネットワークの隣接行列
st_host=load('../../data/st_host.txt')';%戦略を変更しないホストがどれかを表す行列
beta=load('../../data/alpha.txt')';%各ノードの感染確率の行列(転置)
deltaI=load('../../data/deltaI.txt')';%各ノードのマルウェア除去確率の行列(転置)
deltaS=load('../../data/deltaS.txt')';%各ノードの脆弱性除去確率の行列(転置)
eta=load('../../data/eta.txt')';%各ノードの脆弱性発見確率の行列(転置)
tau=0.001;
deltaw=1;
omega=0.05;
kappa=0.1;
t0 = 0; tf = 120; tspan = [t0,tf]; %tの範囲の指定


%自律進化型ボットネットを考慮したnode-base-SIRSモデル%
[t,u] = ode45('ode',tspan,u0);%ode.mの関数node_base_cmの微分方程式を解く
frac=zeros(size(u,1),4);
for i=1:size(u,1)
    frac(i,1)=(sum(u(i,1:num),2)+sum(u(i,3*num+1:4*num),2))/num;
    frac(i,2)=(sum(u(i,num+1:2*num),2)+sum(u(i,4*num+1:5*num),2))/num;
    frac(i,3)=(sum(u(i,2*num+1:3*num),2)+sum(u(i,5*num+1:6*num),2))/num;
    frac(i,4)=(sum(u(i,3*num+1:4*num),2)+sum(u(i,4*num+1:5*num),2)+sum(u(i,5*num+1:6*num),2))/num;
end
%plot(t,u);%t,uのプロット
plot(t,frac(:,1),'-b','Linewidth',2)
hold on
plot(t,frac(:,2),'-r','Linewidth',2)
plot(t,frac(:,3),'-g','Linewidth',2)
plot(t,frac(:,4),'-k','Linewidth',2)
hold off
% % title('node-base感染拡散対策モデル(S)') %タイトルの入力
xlabel('Time','FontSize',20); ylabel('Population Fraction','FontSize',20); %軸の指定
legend('Location','northoutside')%凡例の位置をグラフ外に設定
legend('Orientation','horizontal')
legend('NumColumns',5)
legend('Box','off')
legend('Susceptible','Infected','Recovered','CM','FontSize',15) %凡例の追加と文字の大きさの指定	
filename="beta"+beta(1,1)+"deltai"+deltaI(1,1)+"deltas"+deltaS(1,1)+"eta"+eta(1,1)+"tau"+tau+"deltaw"+deltaw+"omega"+omega+"kappa"+kappa+".svg";
saveas(gcf,filename,'svg')