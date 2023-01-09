#include<bits/stdc++.h>
using namespace std;

int main(void){
    ifstream ifs;
    double n=1000;
    ifs.open("../../../data/ws_adj_mrx.txt");
    vector<double> deg(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double d;
            ifs>>d;
            if(d==1)deg[i]++;
        }
    }
    double ans=0;
    for(auto e:deg)ans+=e;
    ofstream ofs;
    ofs.open("degree.txt");
    ofs<<"各ノードの次数"<<endl;
    for(int i=0;i<n;i++){
        if(i==n-1)ofs<<deg[i]<<endl;
        else ofs<<deg[i]<<" ";
    }
    ofs<<"平均次数"<<endl;
    ofs<<ans/n<<endl;
}