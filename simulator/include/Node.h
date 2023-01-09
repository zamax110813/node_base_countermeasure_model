#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

enum STATE{
    Susceptible1,//非対策脆弱状態
    Infected1,//非対策感染状態
    Recovered1,//非対策保護状態
    Susceptible2,//対策脆弱状態
    Infected2,//対策感染状態
    Recovered2//対策保護状態
};

class Node{
    STATE state;//ノードの状態
    int degree;//次数
    int adj_inf;//隣接する感染ノード数
public:
    Node();
    int get_degree(void);
    int get_adj_inf(void);
    void add_degree(void);
    void sub_degree(void);
    STATE get_state(void);
    void set_state(STATE state);
    void add_adj_inf(void);
    void sub_adj_inf(void);
};

#endif