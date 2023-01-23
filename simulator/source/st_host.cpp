//戦略を変更するホストを0，変更しないホストを1とする(1,n)行列をdataファイルに出力するプログラム。ファイル名はst_host.txt


#include<fstream>

using namespace std;

int main(void){
    ofstream ofs;
    ofs.open("../../data/st_host.txt");
    for(int i=0;i<1000;i++){
        if(i==1||i==17){
            ofs<<1<<" ";
        }else if(i==999){
            ofs<<0<<endl;
        }else{
            ofs<<0<<" ";
        }
    }
    ofs.close();
}