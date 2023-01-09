#include"../include/WS_Graph.h"

//n:全ノード数,e:全エッジ数,k:平均次数,prob:辺の再接続確率,
WS_Graph::WS_Graph(int n,int k,double prob,int init_s1,int init_i1,int init_r1,int init_s2,int init_i2,int init_r2,int input):Graph(n,init_s1,init_i1,init_r1,init_s2,init_i2,init_r2){
    this->reconnect_prob=prob;
    if(input==0){    
        Build_Graph();
        vector<double> used(n,1.0);
        for(int i=0;i<total_s1;i++){
            int tmp=functions::choose(used);
            statevec_s1[tmp]=1;
            nodes[tmp].set_state(Susceptible1);
            used[tmp]=0;
        }
        for(int i=0;i<total_i1;i++){
            int tmp=functions::choose(used);
            statevec_i1[tmp]=1;
            nodes[tmp].set_state(Infected1);
            used[tmp]=0;
            for(int i=0;i<adjacent_list[tmp].size();i++){
                nodes[adjacent_list[tmp][i]].add_adj_inf();
            }
        }
        for(int i=0;i<total_r1;i++){
            int tmp=functions::choose(used);
            statevec_r1[tmp]=1;
            nodes[tmp].set_state(Recovered1);
            used[tmp]=0;
        }
        for(int i=0;i<total_s2;i++){
            int tmp=functions::choose(used);
            statevec_s2[tmp]=1;
            nodes[tmp].set_state(Susceptible2);
            used[tmp]=0;
        }
        for(int i=0;i<total_i2;i++){
            int tmp=functions::choose(used);
            statevec_i2[tmp]=1;
            nodes[tmp].set_state(Infected2);
            used[tmp]=0;
            for(int i=0;i<adjacent_list[tmp].size();i++){
                nodes[adjacent_list[tmp][i]].add_adj_inf();
            }
        }
        for(int i=0;i<total_r2;i++){
            int tmp=functions::choose(used);
            statevec_r2[tmp]=1;
            nodes[tmp].set_state(Recovered2);
            used[tmp]=0;
        }
    }else if(input==1){
        ifstream ifs;
        ifs.open("../../data/ws_adj_mrx.txt");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                ifs>>adjacent_matrix[i][j];
            }
        }
        ifs.close();
        ifs.open("../../data/init_node.txt");
        for(int i=0;i<6;i++){
            for(int j=0;j<n;j++){
                double tmp;
                ifs>>tmp;
                if(i==0){
                    if(tmp){
                        statevec_s1[j]=1.0;
                        nodes[j].set_state(Susceptible1);
                    }
                }else if(i==1){
                    if(tmp){
                        statevec_i1[j]=1.0;
                        nodes[j].set_state(Infected1);
                    }
                }else if(i==2){
                    if(tmp){
                        statevec_r1[j]=1.0;
                        nodes[j].set_state(Recovered1);
                    }
                }else if(i==3){
                    if(tmp){
                        statevec_s2[j]=1.0;
                        nodes[j].set_state(Susceptible2);
                    }
                }else if(i==4){
                    if(tmp){
                        statevec_i2[j]=1.0;
                        nodes[j].set_state(Infected2);
                    }
                }else if(i==5){
                    if(tmp){
                        statevec_r2[j]=1.0;
                        nodes[j].set_state(Recovered2);
                    }
                }
            }
        }
        
        ifs.close();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(adjacent_matrix[i][j]){
                    adjacent_list[i].push_back(j);
                    nodes[i].add_degree();
                }
            }
        }
    }
}

void WS_Graph::handle(Event* p){

}

void WS_Graph::Build_Graph(void){
    for(int i=0;i<(avg_degree/2);i++){
        for(int j=0;j<total_nodes;j++){
            int from=j;
            int to=(i+j+1)%total_nodes;
            adjacent_matrix[from][to]=1;
            adjacent_matrix[to][from]=1;
            nodes[from].add_degree();
            nodes[to].add_degree();
        }
    }
    for(int i=0;i<(avg_degree/2);i++){
        for(int j=0;j<total_nodes;j++){
            int from=j;
            int to=(i+j+1)%total_nodes;
            if(functions::random_double()<reconnect_prob){
                int tmp=functions::random_int(total_nodes);
                if(nodes[tmp].get_degree()>=total_nodes-1)continue;
                if(tmp!=from&&adjacent_matrix[from][tmp]==0){
                    adjacent_matrix[from][to]=0;
                    adjacent_matrix[to][from]=0;
                    nodes[to].sub_degree();
                    adjacent_matrix[from][tmp]=1;
                    adjacent_matrix[tmp][from]=1;
                    nodes[tmp].add_degree();
                }else{
                    while(tmp==from||adjacent_matrix[from][tmp]==1){
                        tmp=functions::random_int(total_nodes);
                    }
                    adjacent_matrix[from][to]=0;
                    adjacent_matrix[to][from]=0;
                    nodes[to].sub_degree();
                    adjacent_matrix[from][tmp]=1;
                    adjacent_matrix[tmp][from]=1;
                    nodes[tmp].add_degree();
                }
            }
        }
    }
    for(int i=0;i<total_nodes;i++){
        for(int j=0;j<total_nodes;j++){
            if(adjacent_matrix[i][j])adjacent_list[i].push_back(j);
        }
    }
}
