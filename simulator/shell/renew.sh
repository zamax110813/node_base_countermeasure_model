#シミュレーションで用いるalpha.txt,deltaI.txt,deltaS.txt,eta.txt,cmp_adj_mrx.txt,init_node.txt,st_host.txtの更新を行うshellscript

n=1000
beta=0.01
deltai=0.1
deltas=0.1
eta=0.001
input_data_path="../../data"

#CMakeでビルド
cmake -S ../source -B ../build
cmake --build ../build

mkdir -p $input_data_path

#alpha.txt,deltaI.txt,deltaS.txt,eta.txtの更新
../build/param $n $beta $deltai $deltas $eta $input_data_path
echo "parameters are ready"

#st_host.txtの更新
../build/st_host
echo "st_host.txt is ready"

#init_node.txtの更新
../build/node_init
echo "init_node.txt is ready"
