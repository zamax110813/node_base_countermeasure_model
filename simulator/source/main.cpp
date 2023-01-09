#include"../include/Complete_Graph.h"
#include"../include/BA_Graph.h"
#include"../include/WS_Graph.h"
#include"../include/Scheduler.h"
#include"../include/Event_Generator.h"
#include<iostream>
#include<sstream>
using namespace std;

namespace parameters{
    double simulation_time;//シミュレーション実行時間
    int num_s1;//初期非対策脆弱ホスト数
    int num_i1;//初期非対策感染ホスト数
    int num_r1;//初期非対策保護ホスト数
    int num_s2;//初期対策脆弱ホスト数
    int num_i2;//初期対策感染ホスト数
    int num_r2;//初期対策保護ホスト数
    int total_nodes;//全ホスト数
    vector<double> alpha;//各ホストのマルウェア感染率
    vector<double> deltas;//各ホストの脆弱性除去率
    vector<double> deltai;//各ホストのマルウェア除去率
    vector<double> eta;//各ホストの脆弱性発見率
    double tau;//対策グループへの参加及び離脱の頻度を表すパラメータ
    double deltaw;//マルウェアの脅威を表す重み
    double omega;//対策グループに参加するホストのコストを表す
    double kappa;//温度係数
    int avg_degree;//グラフの平均次数
    double recon_prob;//グラフの辺の再接続確率
    int graph;//グラフの種類
    int m;//BAモデルのグラフを構築する際の初期の完全グラフのノード数
    double interval;//計測間隔
    string fullpath;//
}

int main(int argc,char *argv[]){
    parameters::simulation_time=atof(argv[1]);
    parameters::total_nodes=atoi(argv[2]);
    parameters::num_s1=atoi(argv[3]);
    parameters::num_i1=atoi(argv[4]);
    parameters::num_r1=atoi(argv[5]);
    parameters::num_s2=atoi(argv[6]);
    parameters::num_i2=atoi(argv[7]);
    parameters::num_r2=atoi(argv[8]);
    parameters::avg_degree=atoi(argv[9]);
    parameters::recon_prob=atof(argv[10]);
    parameters::graph=atoi(argv[11]);
    parameters::interval=atof(argv[12]);
    parameters::m=atoi(argv[13]);
    parameters::tau=atof(argv[14]);
    parameters::deltaw=atof(argv[15]);
    parameters::omega=atof(argv[16]);
    parameters::kappa=atof(argv[17]);
    parameters::fullpath=argv[18];

    Scheduler* scheduler=new Scheduler();

    parameters::alpha.resize(parameters::total_nodes);
    parameters::deltas.resize(parameters::total_nodes);
    parameters::deltai.resize(parameters::total_nodes);
    parameters::eta.resize(parameters::total_nodes);

    ifstream ifs;
    ifs.open(parameters::fullpath+"/alpha.txt");
    if(ifs.fail()){
        cerr<<"Cannot open file"<<endl;
        exit(0);
    }
    string str;
    while(getline(ifs,str)){
        stringstream ss(str);
        for(int i=0;i<parameters::total_nodes;i++)ss>>parameters::alpha[i];
    }
    ifs.close();
    ifs.open(parameters::fullpath+"/deltaS.txt");
    if(ifs.fail()){
        cerr<<"Cannot open file"<<endl;
        exit(0);
    }
    while(getline(ifs,str)){
        stringstream ss(str);
        for(int i=0;i<parameters::total_nodes;i++)ss>>parameters::deltas[i];
    }
    ifs.close();
    ifs.open(parameters::fullpath+"/deltaI.txt");
    if(ifs.fail()){
        cerr<<"Cannot open file"<<endl;
        exit(0);
    }
    while(getline(ifs,str)){
        stringstream ss(str);
        for(int i=0;i<parameters::total_nodes;i++)ss>>parameters::deltai[i];
    }
    ifs.close();
    ifs.open(parameters::fullpath+"/eta.txt");
    if(ifs.fail()){
        cerr<<"Cannot open file"<<endl;
        exit(0);
    }
    while(getline(ifs,str)){
        stringstream ss(str);
        for(int i=0;i<parameters::total_nodes;i++)ss>>parameters::eta[i];
    }
    ifs.close();

    Graph* graph;
    if(parameters::graph==0){
        graph=new Complete_Graph(parameters::total_nodes,parameters::num_s1,parameters::num_i1,parameters::num_r1,parameters::num_s2,parameters::num_i2,parameters::num_r2,1);
    }else if(parameters::graph==1){
        graph=new BA_Graph(parameters::total_nodes,parameters::m,parameters::recon_prob,parameters::num_s1,parameters::num_i1,parameters::num_r1,parameters::num_s2,parameters::num_i2,parameters::num_r2,1);
    }else if(parameters::graph==2){
        graph=new WS_Graph(parameters::total_nodes,parameters::avg_degree,parameters::recon_prob,parameters::num_s1,parameters::num_i1,parameters::num_r1,parameters::num_s2,parameters::num_i2,parameters::num_r2,1);
    }
    Event_Generator* generator=new Event_Generator(parameters::alpha,parameters::deltas,parameters::deltai,parameters::eta,parameters::tau,parameters::deltaw,parameters::omega,parameters::kappa,parameters::interval,graph);
    scheduler->init(parameters::simulation_time);  
    generator->start();
    scheduler->run();
    return 0;
}