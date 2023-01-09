#include"../include/Event_Generator.h"
#include<fstream>
using namespace std;

Event_Generator* Event_Generator::instance_;

Event_Generator::Event_Generator(const vector<double>& beta,const vector<double>& deltas,const vector<double>& deltai,const vector<double>& eta,double tau,double deltaw,double omega,double kappa,double interval,Graph* G){
    this->target_graph=G;
    int n=beta.size();//ネットワーク内のノード数
    this->n=n;
    this->beta.resize(n);
    this->deltas.resize(n);
    this->deltai.resize(n);
    this->eta.resize(n);
    this->tau=tau;
    this->deltaw=deltaw;
    this->omega=omega;
    this->kappa=kappa;
    this->a_beta_I.resize(n);
    for(int i=0;i<n;i++){
        this->beta[i]=beta[i];
        this->deltas[i]=deltas[i];
        this->deltai[i]=deltai[i];
        this->eta[i]=eta[i];
    }
    this->interval=interval;
    rate_vector.assign(9*n,0);

    //rate_vectorの初期化.
    const vector<double>& S1=target_graph->get_s1_vec();
    const vector<double>& I1=target_graph->get_i1_vec();
    const vector<double>& R1=target_graph->get_r1_vec();
    const vector<double>& S2=target_graph->get_s2_vec();
    const vector<double>& I2=target_graph->get_i2_vec();
    const vector<double>& R2=target_graph->get_r2_vec();
    const vector<double>& st_host=target_graph->get_sthost();
    const vector<vector<double>>& A=target_graph->get_adj_mtx();
    eta_I=0;
    int cm=target_graph->get_cm();
    for(int i=0;i<n;i++)eta_I+=eta[i]*(I1[i]+I2[i]);
    for(int i=0;i<n;i++){
        double sum=0;//Σ_j(a_ij*β_j*I_1j*I_2j)
        for(int j=0;j<n;j++)sum+=(double)A[i][j]*(double)beta[j]*(double)(I1[j]+I2[j]);
        a_beta_I[i]=sum;
        rate_vector[9*i]=S1[i]*sum;//S1->I1
        rate_vector[9*i+1]=deltas[i]*S1[i];//S1->R1
        rate_vector[9*i+2]=deltai[i]*I1[i];//I1->R1
        rate_vector[9*i+3]=eta_I*R1[i]*(1-double(cm)/double(n));//R1->S1
        rate_vector[9*i+4]=S2[i]*sum;//S2->I2
        rate_vector[9*i+5]=deltas[i]*S2[i];//S2->R2
        rate_vector[9*i+6]=deltai[i]*I2[i];//I2->R2
        rate_vector[9*i+7]=eta_I*R2[i]*(1-double(cm)/double(n));//R2->S2
        if(st_host[i]==1){
            rate_vector[9*i+8]=0;
            continue;
        }
        //戦略変更の遷移率計算
        double pi1=0,pi2=-omega;
        for(int j=0;j<n;j++)pi1+=A[i][j]*beta[j]*(I1[j]+I2[j]);
        pi1*=(-deltaw);
        double theta12=1/(1+exp((pi1-pi2)/kappa));
        double theta21=1/(1+exp((pi2-pi1)/kappa));
        double phi=0;
        if(S1[i]||I1[i]||R1[i]){
            for(int j=0;j<n;j++)phi+=(A[i][j]*(S2[j]+I2[j]+R2[j]));
            phi*=theta12;
        }else{
            for(int j=0;j<n;j++)phi+=(A[i][j]*(S1[j]+I1[j]+R1[j]));
            phi*=theta21;
        }
        rate_vector[9*i+8]=tau*phi;
    }
    lambda=0;
    for(auto e:rate_vector)lambda+=e;
}

double Event_Generator::culc_interval(){
	return -(log(1.0 - (functions::random_double())))/lambda;
}

//シミュレーション開始時にSchedulerにイベントを登録する関数
void Event_Generator::start(){
  Event* e=new Event;//ネットワーク内の遷移イベント
  Event* p=new Event;//計測イベント
  p->type_of_event=measure;//pのイベントの種類を計測に設定
  set_transition(e);
  Scheduler::instance().schedule(this,e,culc_interval());
  Scheduler::instance().schedule(this,p,0);
}

void Event_Generator::ch_strat(int node_num,const vector<vector<double>>& adj_mtx,const vector<double>& S1,const vector<double>& I1,const vector<double>& R1,const vector<double>& S2,const vector<double>& I2,const vector<double>& R2){
    double pi1=0;
    double pi2=-omega;
    for(int i=0;i<n;i++)pi1+=(adj_mtx[node_num][i]*beta[i]*(I1[i]+I2[i]));
    pi1*=(-deltaw);
    double theta12=1.0/(1+exp(double((pi1-pi2)/kappa)));
    double theta21=1.0/(1+exp((pi2-pi1)/kappa));
    double phi=0;
    if(S1[node_num]||I1[node_num]||R1[node_num]){
        for(int i=0;i<n;i++)phi+=(adj_mtx[node_num][i]*(S2[i]+I2[i]+R2[i]));
        phi*=theta12;
    }else{
        for(int i=0;i<n;i++)phi+=(adj_mtx[node_num][i]*(S1[i]+I1[i]+R1[i]));
        phi*=theta21;
    }
    rate_vector[9*node_num+8]=tau*phi;
}

void Event_Generator::renew_rate(int k,int tran_num){
    const vector<double>& S1=target_graph->get_s1_vec();
    const vector<double>& I1=target_graph->get_i1_vec();
    const vector<double>& R1=target_graph->get_r1_vec();
    const vector<double>& S2=target_graph->get_s2_vec();
    const vector<double>& I2=target_graph->get_i2_vec();
    const vector<double>& R2=target_graph->get_r2_vec();
    const vector<double>& st_host=target_graph->get_sthost();
    const vector<vector<double>>& adjacent_list=target_graph->get_adj_lst();
    int n=target_graph->get_total_nodes();//ネットワーク内のノード数
    int cm=target_graph->get_cm();//対策ホストの数
    for(int i=0;i<n;i++){
        double tmp_a_beta_I=0;
        for(auto e:adjacent_list[i])tmp_a_beta_I+=(beta[e]*(I1[e]+I2[e]));
        rate_vector[9*i]=S1[i]*tmp_a_beta_I;//S1->I1
        rate_vector[9*i+1]=S1[i]*deltas[i];//S1->R1
        rate_vector[9*i+2]=I1[i]*deltai[i];//I1->R1
        double tmp_eta_I=0;
        for(int i=0;i<n;i++)tmp_eta_I+=(eta[i]*(I1[i]+I2[i]));
        rate_vector[9*i+3]=R1[i]*tmp_eta_I*(1-double(cm)/double(n));//R1->S1
        rate_vector[9*i+4]=S2[i]*tmp_a_beta_I;
        rate_vector[9*i+5]=S2[i]*deltas[i];
        rate_vector[9*i+6]=I2[i]*deltai[i];
        rate_vector[9*i+7]=R2[i]*tmp_eta_I*(1-double(cm)/double(n));
        if(st_host[i]==1)continue;
        ch_strat(i,target_graph->get_adj_mtx(),S1,I1,R1,S2,I2,R2);
    }
    lambda=0;
    for(auto e:rate_vector)lambda+=e;
}

void Event_Generator::set_transition(Event* p){
  int i=functions::choose(rate_vector);
  int node_num=i/9;//イベントが起こるノード番号
  i%=9;
  if(i==0){
    p->type_of_event=infection1;
  }else if(i==1){
    p->type_of_event=removal1;
  }else if(i==2){
    p->type_of_event=recovery1;
  }else if(i==3){
    p->type_of_event=discovery1;
  }else if(i==4){
    p->type_of_event=infection2;
  }else if(i==5){
    p->type_of_event=removal2;
  }else if(i==6){
    p->type_of_event=recovery2;
  }else if(i==7){
    p->type_of_event=discovery2;
  }else if(i==8){
    p->type_of_event=change_strat;
  }
  p->node_num=node_num;
}

void Event_Generator::handle(Event* p){
    int s1=target_graph->get_s1_num();
    int s2=target_graph->get_s2_num();
    int i1=target_graph->get_i1_num();
    int i2=target_graph->get_i2_num();
    int r1=target_graph->get_r1_num();
    int r2=target_graph->get_r2_num();
    if(p->type_of_event==measure){//計測イベントが呼ばれた時の処理
        
        cout<<fixed<<setprecision(15)<<p->time<<" "<<double(s1+s2)/n<<" "<<double(i1+i2)/n<<" "<<double(r1+r2)/n<<" "<<double(s2+i2+r2)/double(n)<<endl;

        Event* e=new Event;
        e->type_of_event=measure;
        Scheduler::instance().schedule(this,e,interval);
        return;
    }else{
        //rateを記録
        ofstream ofs;
        ofs.open("../data/rate.txt",ios::app);
        ofs<<fixed<<setprecision(5)<<"time : "<<p->time<<" ";
        vector<double> rate(9,0);
        for(int i=0;i<1000;i++){
            for(int j=0;j<9;j++){
                rate[j]+=rate_vector[9*i+j];
            }
        }
        ofs<<fixed<<setprecision(5)<<"S : "<<s1+s2<<" "<<"I : "<<i1+i2<<" "<<"R : "<<r1+r2<<" ";
        for(int i=0;i<9;i++){
            if(i==8)ofs<<rate[i]<<endl;
            else ofs<<rate[i]<<" ";
        }
        ofs.close();
        target_graph->recv(p);
        renew_rate(p->node_num,p->type_of_event);
        Event* e=new Event;
        set_transition(e);
        Scheduler::instance().schedule(this,e,culc_interval());
    }
}

void Event_Generator::recv(Event* p){

}