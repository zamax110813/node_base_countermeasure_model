#ifndef EVENT_GENERATOR_H
#define EVENT_GENERATOR_H

#include"Obj.h"
#include<iostream>
#include<iomanip>
#include"Graph.h"
#include"functions.h"
#include"Scheduler.h"
#include<vector>

using namespace std;

class Event_Generator:public Obj{
  public:
    static Event_Generator& instance(){
      return (*instance_);
    };
    Event_Generator(const vector<double>& beta,const vector<double>& deltas,const vector<double>& deltai,const vector<double>& eta,double tau,double deltaw,double omega,double kappa,double interval,Graph* G);
    void start();
    void handle(Event* p);
    void recv(Event* p);
    void ch_strat(int node_num,const vector<vector<double> >& adj_mtx,const vector<double>& S1,const vector<double>& I1,const vector<double>& R1,const vector<double>& S2,const vector<double>& I2,const vector<double>& R2);//戦略を変更する遷移率τΦを計算
    void renew_rate(int k,int tran_num);//k:イベントの起きたノード番号, tran_num:遷移番号
    void set_transition(Event *p);
  private:
    Graph* target_graph;//対象グラフのアドレスを保持するポインタ
    double culc_interval();//イベントの発生間隔を計算する関数
    int n;//ネットワーク内のノード数
    vector<double> a_beta_I;
    double eta_I;
    vector<double> beta;//各ノードの単位時間当たりの感染確率α_i
    vector<double> deltas;//各ノードの単位時間当たりの脆弱性除去確率δ_si
    vector<double> deltai;//各ノードの単位時間当たりの回復確率δ_Ii
    vector<double> eta;//各ノードの単位時間当たりの脆弱性発見確率η_i
    double tau;//対策グループへの参加及び離脱の頻度を表すパラメータ
    double deltaw;//マルウェアの脅威を表す重み
    double omega;//対策グループに参加するホストのコストを表す
    double kappa;//温度係数
    double lambda;//遷移確率の総和
    double interval;//ネットワークの状態を記録するイベントの発生間隔
    vector<double> rate_vector;//遷移確率の行列.1+4*(N-1)番目の要素はノードNがS→Iに遷移する確率，2+4*(N-1)番目の要素はノードNがS→Rに遷移する確率，3+4*(N-1)番目の要素はノードNがI→Rに遷移する確率，4+4*(N-1)番目の要素はノードNがR→Sに遷移する確率を表す
    static Event_Generator* instance_;
};


#endif
#pragma once