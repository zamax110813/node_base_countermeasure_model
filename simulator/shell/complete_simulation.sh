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
interval : データ記録間隔
simu_num : シミュレーション回数
m : BAモデルのグラフを構築する際の初期の完全グラフのノード数
tau : 対策グループへの参加及び離脱の頻度を表すパラメータ
deltaw : マルウェアの脅威を表す重み
omega : 対策グループに参加するホストのコストを表す
kappa : 温度係数
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
input_data_path="../../data/node_param/homo/${beta}/${deltai}/${deltas}/${eta}"
output_data_path="../data/CompleteGraph/${n}nodes/${init_s1}.${init_i1}.${init_r1}.${init_s2}.${init_i2}.${init_r2}/sthosts${sthosts}/simu_num${simu_num}/beta${beta}/deltai${deltai}/deltas${deltas}/eta${eta}/tau${tau}/deltaw${deltaw}/omega${omega}/kappa${kappa}"
graph_path="../results/CompleteGraph/${n}nodes/${init_s1}.${init_i1}.${init_r1}.${init_s2}.${init_i2}.${init_r2}/sthosts${sthosts}/simu_num${simu_num}/beta${beta}/deltai${deltai}/deltas${deltas}/eta${eta}/tau${tau}/deltaw${deltaw}/omega${omega}/kappa${kappa}"

#cmakeでビルド，コンパイル 
cmake -S ../source -B ../build
cmake --build ../build

mkdir -p $input_data_path

../build/param $n $beta $deltai $deltas $eta $input_data_path
 
for i in `seq 0 $simu_num`
do
rm -f "${output_data_path}/output${i}.dat"
done
 
mkdir -p $output_data_path
 
for i in `seq 0 $simu_num`
do
tmp="${output_data_path}/output${i}.dat"
../build/a.out $t $n $init_s1 $init_i1 $init_r1 $init_s2 $init_i2 $init_r2 $k $p $graph $interval  $m $tau $deltaw $omega $kappa $input_data_path>$tmp
echo $i
done
 
../build/average $t $interval $simu_num $output_data_path

mkdir -p $graph_path 

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
