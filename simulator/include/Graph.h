#ifndef INCLUDED_GRAPH_H
#define INCLUDED_GRAPH_H

#include<vector>
#include<iostream>
#include"Node.h"
#include"Obj.h"
#include"functions.h"

using namespace std;

class Graph:public Obj{
protected:
    int total_nodes;//全ノード数
    int cm;//対策ホスト数
    int ncm;//非対策ホスト数
    int total_s1;//非対策脆弱ホスト数
    int total_i1;//非対策感染ホスト数
    int total_r1;//非対策保護ホスト数
    int total_s2;//対策脆弱ホスト数
    int total_i2;//対策感染ホスト数
    int total_r2;//対策保護ホスト数
    int avg_degree;//平均次数
    vector<double> statevec_s1;//非対策脆弱状態かどうかの配列 
    vector<double> statevec_i1;//非対策感染状態かどうかの配列 
    vector<double> statevec_r1;//非対策保護状態かどうかの配列 
    vector<double> statevec_s2;//対策脆弱状態かどうかの配列 
    vector<double> statevec_i2;//対策感染状態かどうかの配列 
    vector<double> statevec_r2;//対策保護状態かどうかの配列 
    vector<double> st_host;//戦略を変更しないホストかどうかの配列
    vector<vector<double> > adjacent_matrix;//隣接行列
    vector<vector<double> > adjacent_list;//隣接リスト
    vector<Node> nodes;//各ホストを格納する配列
public:
    Graph(int n,int s1,int i1,int r1,int s2,int i2,int r2);
    int get_total_nodes(void);
    const vector<double>& get_s1_vec(void);
    const vector<double>& get_i1_vec(void);
    const vector<double>& get_r1_vec(void);
    const vector<double>& get_s2_vec(void);
    const vector<double>& get_i2_vec(void);
    const vector<double>& get_r2_vec(void);
    const vector<double>& get_sthost(void);
    int get_s1_num(void);
    int get_i1_num(void);
    int get_r1_num(void);
    int get_s2_num(void);
    int get_i2_num(void);
    int get_r2_num(void);
    int get_cm(void);
    const vector<vector<double> >& get_adj_mtx(void);
    const vector<vector<double> >& get_adj_lst(void);
    void out_params(void);
    void out_graph(void);
    virtual void Build_Graph(void)=0;
    virtual void handle(Event* p)=0;
    void recv(Event* p);
};

#endif