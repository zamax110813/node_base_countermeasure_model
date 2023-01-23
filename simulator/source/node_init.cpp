#include<bits/stdc++.h>

using namespace std;

int main(void){
    cout<<"ノード数を入力"<<endl;
    int n;
    cin>>n;
    vector<double> S1(n,1),I1(n,0),R1(n,0),S2(n,0),I2(n,0),R2(n,0);
    I1[17]=1.0;
    S1[17]=0;
    S2[1]=1;
    S1[1]=0;
    string fullpath="../../data/";
    ofstream ofs;
    string datafile="init_node.txt";
    fullpath+=datafile;
    ofs.open(fullpath);
    if(!ofs){
        cerr<<"ファイルオープンに失敗"<<endl;
        exit(1);
    }
    for(int i=0;i<n;i++){
        ofs<<S1[i]<<" ";
    }
    for(int i=0;i<n;i++){
        ofs<<I1[i]<<" ";
    }
    for(int i=0;i<n;i++){
        ofs<<R1[i]<<" ";
    }
    for(int i=0;i<n;i++){
        ofs<<S2[i]<<" ";
    }
    for(int i=0;i<n;i++){
        ofs<<I2[i]<<" ";
    }
    for(int i=0;i<n;i++){
        if(i!=n-1)ofs<<R2[i]<<" ";
        else ofs<<R2[i]<<endl;
    }
}