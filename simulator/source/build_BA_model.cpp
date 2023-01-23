#include<bits/stdc++.h>
#include"../include/functions.h"
using namespace std;

int main(int argc,char* argv[]){
    int n;//ネットワーク内のホスト数
    int m;//始めに構成する完全グラフのホスト数

    n=atoi(argv[1]);
    m=atoi(argv[2]);

    vector<double> degree(n,0);//ホスト毎の次数
    vector<vector<int>> adjacent_matrix(n,vector<int>(n,0));//隣接行列

    int max_degree=0;//最も大きい次数
    int max_degree_idx=0;//最も大きい次数を持つホスト番号

    int min_degree=n;//最も小さい次数
    int min_degree_idx=0;//最も小さい次数を持つホスト番号


    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(i==j||adjacent_matrix[i][j])continue;
            adjacent_matrix[i][j]=1;
            adjacent_matrix[j][i]=1;
            degree[i]++;
            degree[j]++;
        }
    }

    for(int i=m;i<n;i++){
        vector<double> tmp=degree;
        for(int j=0;j<m;j++){
            int idx=functions::choose(tmp);
            adjacent_matrix[i][idx]=1;
            adjacent_matrix[idx][i]=1;
            degree[i]++;
            degree[idx]++;
            tmp[idx]=0;
        }
    }

    for(int i=0;i<n;i++){
        int tmp_degree=0;
        for(int j=0;j<n;j++){
            if(adjacent_matrix[i][j])tmp_degree++;
        }
        if(tmp_degree>max_degree){
            max_degree=tmp_degree;
            max_degree_idx=i;
        }
        if(tmp_degree<min_degree){
            min_degree=tmp_degree;
            min_degree_idx=i;
        }
    }

    string outpath="../../data/ba_adj_mrx.txt";
    ofstream ofs;
    ofs.open(outpath);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==n-1)ofs<<adjacent_matrix[i][j]<<endl;
            else ofs<<adjacent_matrix[i][j]<<" ";
        }
    }
    ofs.close();

    outpath="../../data/ba_degree_info.txt";
    ofs.open(outpath);
    for(int i=0;i<n;i++){
        if(i==n-1)ofs<<degree[i]<<endl;
        else ofs<<degree[i]<<" ";
    }
    ofs.close();

    outpath="../../data/ba_model_info.txt";
    ofs.open(outpath);
    ofs<<"最小次数 : "<<min_degree<<endl;
    ofs<<"最小次数を持つホストの番号 : "<<min_degree_idx<<endl;
    ofs<<"最大次数 : "<<max_degree<<endl;
    ofs<<"最大次数を持つホストの番号 : "<<max_degree_idx<<endl;
    ofs.close();
}
