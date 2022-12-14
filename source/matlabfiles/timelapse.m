global beta deltaS deltaI eta A num tau deltaw omega kappa;
u = load('../../data/init_node.txt')';
prob=zeros(6*num,1);%6*num行1列の遷移率行列(初期値は全て0)
phiS=zeros(num,1);
phiI=zeros(num,1);
phiR=zeros(num,1);
pi2=-omega;
for i=1:num
    pi1=-deltaw*sum(A(:,i).*(beta.*(u(num+1:2*num,1)+u(4*num+1:5*num,1))));
    theta12=1/(1+exp((pi1-pi2)/kappa));
    theta21=1/(1+exp((pi2-pi1)/kappa));
    frac1=sum(A(:,i).*(u(1:num,1)+u(num+1:2*num,1)+u(2*num+1:3*num,1)));
    frac2=sum(A(:,i).*(u(3*num+1:4*num,1)+u(4*num+1:5*num,1)+u(5*num+1:6*num,1)));
    phiS(i,1)=u(3*num+i,1)*frac1*theta21...
        -u(i,1)*frac2*theta12;
    phiI(i,1)=u(4*num+i,1)*frac1*theta21...
        -u(num+i,1)*frac2*theta12;
    phiR(i,1)=u(5*num+i,1)*frac1*theta21...
        -u(2*num+i,1)*frac2*theta12;
    %S_1i(t)に関する微分方程式
    abetaI1I2=sum(A(:,i).*(beta.*(u(num+1:2*num,1)+u(4*num+1:5*num,1))));
    R1S1=sum(eta.*(u(num+1:2*num,1)+u(4*num+1:5*num,1)))*(1-sum(u(3*num+1:4*num,1)+u(4*num+1:5*num,1)+u(5*num+1:6*num,1))/num);
    prob(i,1)=-u(i,1)*abetaI1I2...
        -deltaS(i,1)*u(i,1)...
        +u(2*num+i,1)*R1S1...
        +tau*phiS(i,1);
    %I_1i(t)に関する微分方程式
    prob(num+i,1)=u(i,1)*abetaI1I2...
        -deltaI(i,1)*u(num+i,1)...
        +tau*phiI(i,1);
    %R_1i(t)に関する微分方程式
    prob(2*num+i,1)=deltaI(i,1)*u(num+i,1)...
        +deltaS(i,1)*u(i,1)...
        -u(2*num+i,1)*R1S1...
        +tau*phiR(i,1);
    %S_2i(t)に関する微分方程式
    prob(3*num+i,1)=-u(3*num+i,1)*abetaI1I2...
        -deltaS(i,1)*u(3*num+i,1)...
        +u(5*num+i,1)*R1S1...
        -tau*phiS(i,1);
    %I_2i(t)に関する微分方程式
    prob(4*num+i,1)=u(3*num+i,1)*abetaI1I2...
        -deltaI(i,1)*u(4*num+i,1)...
        -tau*phiI(i,1);
    %R_2i(t)に関する微分方程式
    prob(5*num+i,1)=deltaI(i,1)*u(4*num+i,1)...
        +deltaS(i,1)*u(3*num+i,1)...
        -u(5*num+i,1)*R1S1...
        -tau*phiR(i,1);
end    