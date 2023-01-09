//各シミュレーションデータが数値解析と同じ結果になっているか判定するプログラム
//入力はコマンドライン引数からデータファイルのパスと数値解析での感染の広がり方を表す数値
//出力は数値解析と同じ感染の広がり方なら0,そうでないなら1を出力
#include<bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[]){
    int howtospread=atoi(argv[1]);//コマンドライン引数から数値解析での広がり方を表す数値を取得
    string filepath=argv[2];
    bool flag=true;//数値解析と同じ結果になっているか判別するフラグ(同じならtrue，異なるならfalse)
    ifstream ifs;
    ifs.open(filepath);
    double max_i=0;//感染ホスト数割合の最大値
    double last_i;
    double t,s,i,r,c;
    while(!ifs.eof()){
        ifs>>t>>s>>i>>r>>c;
        last_i=i;
        if(howtospread==1&&i==0){//数値解析では感染を繰り返すが，シミュレーションでは感染が収束した場合
            flag=false;
            break;
        }
        if(max_i<i){
            max_i=i;
        }
    }
    if(howtospread==0){
        if(max_i>0.1&&last_i==0)flag=true;
        else flag=false;
    }
    if(flag)cout<<0<<endl;
    else cout<<1<<endl;
}