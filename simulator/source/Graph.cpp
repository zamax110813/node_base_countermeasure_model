#include"../include/Graph.h"

Graph::Graph(int n,int s1,int i1,int r1,int s2,int i2,int r2){
    total_nodes=n;
    statevec_s1.assign(total_nodes,0);
    statevec_i1.assign(total_nodes,0);
    statevec_r1.assign(total_nodes,0);
    statevec_s2.assign(total_nodes,0);
    statevec_i2.assign(total_nodes,0);
    statevec_r2.assign(total_nodes,0);
    st_host.assign(total_nodes,0);
    total_s1=s1;
    total_i1=i1;
    total_r1=r1;
    total_s2=s2;
    total_i2=i2;
    total_r2=r2;
    cm=s2+i2+r2;
    ncm=s1+i1+r1;
    adjacent_matrix.assign(total_nodes,vector<double>(total_nodes,0));
    adjacent_list.resize(total_nodes);
    nodes.assign(total_nodes,Node());
}

void Graph::recv(Event* p){
    switch(p->type_of_event){
        //R1->S1への遷移
        case discovery1:
        {
            int index=p->node_num;
            nodes[index].set_state(Susceptible1);
            statevec_r1[index]=0;
            statevec_s1[index]=1;
            total_r1--;
            total_s1++;
            return;
        }
        case removal1://S1->R1への遷移
        {
            int index=p->node_num;
            nodes[index].set_state(Recovered1);
            statevec_s1[index]=0;
            statevec_r1[index]=1;
            total_s1--;
            total_r1++;
            return;
        }
        case infection1://S1->I1への遷移
        {
            int index=p->node_num;
            nodes[index].set_state(Infected1);//状態変更
            total_i1++;
            total_s1--;
            statevec_i1[index]=1;
            statevec_s1[index]=0;
            return;
        }
        case recovery1://I1->R1への遷移
        {
            int index=p->node_num;
            nodes[index].set_state(Recovered1);
            total_i1--;
            total_r1++;
            statevec_i1[index]=0;
            statevec_r1[index]=1;
            return ;
        }
        case discovery2:
        {
            int index=p->node_num;
            nodes[index].set_state(Susceptible2);
            statevec_r2[index]=0;
            statevec_s2[index]=1;
            total_r2--;
            total_s2++;
            return;
        }
        case removal2://S->Rへの遷移
        {
            int index=p->node_num;
            nodes[index].set_state(Recovered2);
            statevec_s2[index]=0;
            statevec_r2[index]=1;
            total_s2--;
            total_r2++;
            return;
        }
        case infection2://S2->I2への遷移
        {
            int index=p->node_num;
            nodes[index].set_state(Infected2);//状態変更
            total_i2++;
            total_s2--;
            statevec_i2[index]=1;
            statevec_s2[index]=0;
            return;
        }
        case recovery2://I2->R2への遷移
        {
            int index=p->node_num;
            nodes[index].set_state(Recovered2);
            total_i2--;
            total_r2++;
            statevec_i2[index]=0;
            statevec_r2[index]=1;
            return ;
        }
        case change_strat:
        {
            int index=p->node_num;
            int nodes_state=nodes[index].get_state();
            if(nodes_state>=0&&nodes_state<=2){
                if(nodes_state==Susceptible1){
                    nodes[index].set_state(Susceptible2);
                    total_s1--;
                    total_s2++;
                    statevec_s1[index]=0;
                    statevec_s2[index]=1;
                }else if(nodes_state==Infected1){
                    nodes[index].set_state(Infected2);
                    total_i1--;
                    total_i2++;
                    statevec_i1[index]=0;
                    statevec_i2[index]=1;
                }else if(nodes_state==Recovered1){
                    nodes[index].set_state(Recovered2);
                    total_r1--;
                    total_r2++;
                    statevec_r1[index]=0;
                    statevec_r2[index]=1;
                }
                ncm--;
                cm++;
            }else{
                if(nodes_state==Susceptible2){
                    nodes[index].set_state(Susceptible1);
                    total_s1++;
                    total_s2--;
                    statevec_s2[index]=0;
                    statevec_s1[index]=1;
                }else if(nodes_state==Infected2){
                    nodes[index].set_state(Infected1);
                    total_i2--;
                    total_i1++;
                    statevec_i2[index]=0;
                    statevec_i1[index]=1;
                }else if(nodes_state==Recovered2){
                    nodes[index].set_state(Recovered1);
                    total_r2--;
                    total_r1++;
                    statevec_r2[index]=0;
                    statevec_r1[index]=1;
                }
                cm--;
                ncm++;
            }
            return;
        }
    }
}

void Graph::out_params(void){
    cout<<"total_nodes : "<<total_nodes<<" ";
    cout<<"total_s1 : "<<total_s1<<" ";
    cout<<"total_i1 : "<<total_i1<<" ";
    cout<<"total_r1 : "<<total_r1<<" ";
    cout<<"avg_degree : "<<avg_degree<<endl;
}

void Graph::out_graph(void){
    for(int i=0;i<total_nodes;i++){
        for(int j=0;j<adjacent_list[i].size();j++){
            cout<<adjacent_list[i][j]<<" ";
        }
        cout<<endl;
    }
}

int Graph::get_total_nodes(void){
    return total_nodes;
}

const vector<double>& Graph::get_s1_vec(void){
    return statevec_s1;
}

const vector<double>& Graph::get_i1_vec(void){
    return statevec_i1;
}

const vector<double>& Graph::get_r1_vec(void){
    return statevec_r1;
}

const vector<double>& Graph::get_s2_vec(void){
    return statevec_s2;
}

const vector<double>& Graph::get_i2_vec(void){
    return statevec_i2;
}

const vector<double>& Graph::get_r2_vec(void){
    return statevec_r2;
}

const vector<double>& Graph::get_sthost(void){
    return st_host;
}

int Graph::get_s1_num(void){
    return this->total_s1;
}

int Graph::get_i1_num(void){
    return this->total_i1;
}

int Graph::get_r1_num(void){
    return this->total_r1;
}

int Graph::get_s2_num(void){
    return this->total_s2;
}

int Graph::get_i2_num(void){
    return this->total_i2;
}

int Graph::get_r2_num(void){
    return this->total_r2;
}

int Graph::get_cm(void){
    return this->cm;
}

const vector<vector<double> >& Graph::get_adj_mtx(void){
    return adjacent_matrix;
}

const vector<vector<double> >& Graph::get_adj_lst(void){
    return adjacent_list;
}