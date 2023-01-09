#include<bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[]){
    int n;
    double alpha,deltai,deltas,e;
    n=atoi(argv[1]);
    alpha=atof(argv[2]);
    deltai=atof(argv[3]);
    deltas=atof(argv[4]);
    e=atof(argv[5]);
    string fullpath=argv[6];
    fullpath+="/";
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