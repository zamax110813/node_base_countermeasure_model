#include<vector>
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;
 
int main(int argc,char *argv[]){
   double simulation_time=atof(argv[1]);
   double interval=atof(argv[2]);
   int simu_num=atoi(argv[3]);
   string path=argv[4];
   int folder_num=atoi(argv[5]);
   int rec_num=simulation_time/interval+1;
   vector<double> S(rec_num,0),I(rec_num,0),R(rec_num,0),CM(rec_num,0);
   string output="/output",ext=".dat";
   for(int k=0;k<folder_num;k++){
        for(int i=1;i<=10;i++){
            ifstream ifs;
            int from=k*10+1;
            int to=10*(k+1);
            string tmp_path=path+"/"+to_string(from)+"_"+to_string(to);
            string datafile=output+to_string(i)+ext;
            ifs.open(tmp_path+datafile);
            if(ifs.fail()){
                cout<<"Failed to open file."<<endl;
                return -1;
            }
            string str;
            double temp_t,temp_s,temp_i,temp_r,temp_cm;
            for(int j=0;j<rec_num;j++){
                getline(ifs,str);
                stringstream ss(str);
                ss>>temp_t>>temp_s>>temp_i>>temp_r>>temp_cm;
                S[j]+=temp_s;
                I[j]+=temp_i;
                R[j]+=temp_r;
                CM[j]+=temp_cm;
            }
            ifs.close();
        }
   }
   
   ofstream ofs;
   ofs.open(path+output+ext);
   if(ofs.fail()){
       cout<<"Failed to open file."<<endl;
       return -1;
   }
   double time=0;
   for(int i=0;i<rec_num;i++){
       ofs<<fixed<<setprecision(15)<<time<<" "<<S[i]/simu_num<<" "<<I[i]/simu_num<<" "<<R[i]/simu_num<<" "<<CM[i]/simu_num<<endl;
       time+=interval;
   }
   ofs.close();
}
