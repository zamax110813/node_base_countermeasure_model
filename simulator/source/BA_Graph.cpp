#include"../include/BA_Graph.h"

//n:全ノード数,e:全エッジ数,k:平均次数,prob:辺の再接続確率,
BA_Graph::BA_Graph(int n,int m,double prob,int init_s1,int init_i1,int init_r1,int init_s2,int init_i2,int init_r2,int k):Graph(n,init_s1,init_i1,init_r1,init_s2,init_i2,init_r2){
    this->m=m;
    if(k==0){
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
        }
        for(int i=0;i<total_r2;i++){
            int tmp=functions::choose(used);
            statevec_r2[tmp]=1;
            nodes[tmp].set_state(Recovered2);
            used[tmp]=0;
        }
    }else if(k==1){
        ifstream ifs;
        ifs.open("../../data/ba_adj_mrx.txt");
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

void BA_Graph::handle(Event* p){

}

void BA_Graph::Build_Graph(void){
    vector<double> degree(total_nodes,0);
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(i==j||adjacent_matrix[i][j])continue;
            adjacent_matrix[i][j]=1;
            adjacent_matrix[j][i]=1;
            nodes[i].add_degree();
            nodes[j].add_degree();
            degree[i]++;
            degree[j]++;
        }
    }
    for(int i=m;i<total_nodes;i++){
        vector<double> tmp=degree;
        for(int j=0;j<m;j++){
            int idx=functions::choose(tmp);
            adjacent_matrix[i][idx]=1;
            adjacent_matrix[idx][i]=1;
            nodes[i].add_degree();
            nodes[idx].add_degree();
            degree[i]++;
            degree[idx]++;
            tmp[idx]=0;
        }
    }
    for(int i=0;i<total_nodes;i++){
        for(int j=0;j<total_nodes;j++){
            if(adjacent_matrix[i][j])adjacent_list[i].push_back(j);
        }
    }
}
