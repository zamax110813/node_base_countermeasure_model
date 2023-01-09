#include<bits/stdc++.h>
using namespace std;

int main(void){
    cout<<"ノード数を入力してください"<<endl;
    int n;
    cin>>n;
    double alpha,deltai,deltas,e;
    cout<<"感染率を入力してください"<<endl;
    cin>>alpha;
    cout<<"回復率を入力してください"<<endl;
    cin>>deltai;
    cout<<"脆弱性除去率を入力してください"<<endl;
    cin>>deltas;
    cout<<"脆弱性発見率を入力してください"<<endl;
    cin>>e;
    string fullpath="../../../data/";
    ofstream ofs;
    vector<double> alphai(n,alpha);
    vector<double> deltaI(n,deltai);
    vector<double> deltaS(n,deltas);
    vector<double> eta(n,e);
    string datafile="alpha.txt";
    ofs.open(fullpath+datafile);
    if(!ofs){
        cerr<<"ファイルオープンに失敗"<<endl;
        exit(1);
    }
    for(int i=0;i<n;i++){
        if(i==n-1)ofs<<alphai[i]<<endl;
        else ofs<<alphai[i]<<" ";
    }
    ofs.close();
    datafile="deltaI.txt";
    ofs.open(fullpath+datafile);
    if(!ofs){
        cerr<<"ファイルオープンに失敗"<<endl;
        exit(1);
    }
    for(int i=0;i<n;i++){
        if(i==n-1)ofs<<deltaI[i]<<endl;
        else ofs<<deltaI[i]<<" ";
    }
    ofs.close();
    datafile="deltaS.txt";
    ofs.open(fullpath+datafile);
    if(!ofs){
        cerr<<"ファイルオープンに失敗"<<endl;
        exit(1);
    }
    for(int i=0;i<n;i++){
        if(i==n-1)ofs<<deltaS[i]<<endl;
        else ofs<<deltaS[i]<<" ";
    }
    ofs.close();
    datafile="eta.txt";
    ofs.open(fullpath+datafile);
    if(!ofs){
        cerr<<"ファイルオープンに失敗"<<endl;
        exit(1);
    }
    for(int i=0;i<n;i++){
        if(i==n-1)ofs<<eta[i]<<endl;
        else ofs<<eta[i]<<" ";
    }
    ofs.close();
}
