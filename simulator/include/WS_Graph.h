#ifndef WS_GRAPH_H
#define WS_GRAPH_H

#include<fstream>
#include"Node.h"
#include"Graph.h"
#include"Event.h"
#include"functions.h"

using namespace std;

class WS_Graph:public Graph{
private:
    double reconnect_prob;//辺の再接続確率
public:
    WS_Graph(int n,int k,double prob,int init_s1,int init_i1,int init_r1,int init_s2,int init_i2,int init_r2,int input);
    void Build_Graph(void) override;
    void handle(Event* p);
};

#endif