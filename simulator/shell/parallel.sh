:<<'#COMMENTOUT'
自立進化型ボットネットのnode-base-SIRSモデルの確率論的シミュレータ
パラメータ
t : シミュレーション時間
n : 全ノード数
k : 接続する隣接ノード数
p : ノード再接続の確率
graph : グラフの種類.0 : 完全グラフ, 1 : BAグラフ, 2 : WAグラフ
init_s1 : 初期状態における非対策脆弱ホスト数
init_i1 : 初期状態における非対策感染ホスト数
init_r1 : 初期状態における非対策保護ホスト数
init_s2 : 初期状態における対策脆弱ホスト数
init_i2 : 初期状態における対策感染ホスト数
init_r2 : 初期状態における対策保護ホスト数
sthosts : 戦略を変更しないホスト数
interval : データ記録間隔
simu_num : シミュレーション回数
m : BAモデルのグラフを構築する際の初期の完全グラフのノード数
tau : 対策グループへの参加及び離脱の頻度を表すパラメータ
deltaw : マルウェアの脅威を表す重み
omega : 対策グループに参加するホストのコストを表す
kappa : 温度係数
beta : 単位時間あたりに感染ノードが隣接ノードに感染させる確率
deltai : 単位時間あたりに感染ノードが保護ノードに遷移する確率
deltas : 単位時間あたりに脆弱ノードが保護ノードに遷移する確率
eta : 単位時間あたりに感染ノードが脆弱性を発見する確率
thread_num : 並列で実行するシミュレーション数
howtospread : 数値解析での感染の広がり方
input_data_path : alpha.txt,deltai.txt,deltas.txt,eta.txtを格納しているパス
output_data_path : シミュレーションデータを格納するパス
graph_path : シミュレーションのグラフを格納するパス
#COMMENTOUT
t=$1
n=$2
k=$3
p=$4
graph=$5
init_s1=$6
init_i1=$7
init_r1=$8
init_s2=$9
init_i2=${10}
init_r2=${11}
sthosts=${12}
interval=${13}
simu_num=${14}
m=${15}
tau=${16}
deltaw=${17}
omega=${18}
kappa=${19}
beta=${20}
deltai=${21}
deltas=${22}
eta=${23}
thread_num=${24}   
howtospread=${25}
folder_num=$(($simu_num/$thread_num))   #作成する出力データ格納用フォルダの個数
input_data_path="../../data/node_param/homo/${beta}/${deltai}/${deltas}/${eta}"#入力パラメータファイルのパス
output_data_path="../data/CompleteGraph/${n}nodes/${init_s1}.${init_i1}.${init_r1}.${init_s2}.${init_i2}.${init_r2}/sthosts${sthosts}/simu_num${simu_num}/beta${beta}/deltai${deltai}/deltas${deltas}/eta${eta}/tau${tau}/deltaw${deltaw}/omega${omega}/kappa${kappa}"#シミュレーション結果の出力パス
graph_path="../results/CompleteGraph/${n}nodes/${init_s1}.${init_i1}.${init_r1}.${init_s2}.${init_i2}.${init_r2}/sthosts${sthosts}/simu_num${simu_num}/beta${beta}/deltai${deltai}/deltas${deltas}/eta${eta}/tau${tau}/deltaw${deltaw}/omega${omega}/kappa${kappa}"#グラフを格納するパス

#CMakeでソースファイルをビルド
cmake -S ../source -B ../build
cmake --build ../build

#入力データを配置するディレクトリを作成
mkdir -p $input_data_path

#パラメータを設定
../build/param $n $beta $deltai $deltas $eta $input_data_path

#前回行ったシミュレーションで用いたecho.txtが残っていれば削除
rm -f echo.txt 

#echo.txtの作成
#echo.txtにはxargsコマンドでsimu.shに渡す引数が書かれている
for i in `seq 1 $folder_num`
do
from=$((10*(${i}-1)+1))
to=$((10*${i}))
tmp_path="${output_data_path}/${from}_${to}" #単体のシミュレーションデータを出力するパス(例 : 1~10回目のシミュレーションのデータは1_10に出力)
mkdir -p $tmp_path
echo $t $n $init_s1 $init_i1 $init_r1 $init_s2 $init_i2 $init_r2 $k $p $graph $interval  $m $tau $deltaw $omega $kappa $input_data_path $tmp_path $howtospread>>echo.txt # >>は追記
done

echo "simulation start."

#並列で実行
xargs -a ./echo.txt -L 1 -P $thread_num ./simu.sh

#データの平均を取って出力
../build/average $t $interval $simu_num $output_data_path $folder_num

#グラフ出力用のパスを作成
mkdir -p $graph_path 

#グラフの出力
gnuplot -persist <<EOF
set yrange [0:1]
set xrange [0:$t]
set xlabel "time"
set ylabel "fraction"
set nokey
plot "${output_data_path}/output.dat" u 1:2 title "S(Susceptible)" w l lw 3 lc 'blue',\
"${output_data_path}/output.dat" u 1:3 title "I(Infected)" w l lw 3 lc 'red',\
"${output_data_path}/output.dat" u 1:4 title "R(Recovered)" w l lw 3 lc 'green',\
"${output_data_path}/output.dat" u 1:5 title "Countermeasure" w l lw 3 lc 'black'
set terminal svg
set output "${graph_path}/result.svg"
replot
EOF
