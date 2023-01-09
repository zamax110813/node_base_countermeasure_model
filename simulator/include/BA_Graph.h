#ifndef BA_GRAPH_H
#define BA_GRAPH_H

#include<iostream>
#include<fstream>
#include"Node.h"
#include"Graph.h"
#include"Event.h"
#include"functions.h"

using namespace std;

class BA_Graph:public Graph{
private:
    double m;//初期の完全グラフの頂点数
public:
    BA_Graph(int n,int m,double prob,int init_s1,int init_i1,int init_r1,int init_s2,int init_i2,int init_r2,int k);
    void Build_Graph(void) override;
    void handle(Event* p);
};

#endif