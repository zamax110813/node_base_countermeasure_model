t=$1
n=$2
init_s1=$3
init_i1=$4
init_r1=$5
init_s2=$6
init_i2=$7
init_r2=$8
k=$9
p=${10}
graph=${11}
interval=${12}
m=${13}
tau=${14}
deltaw=${15}
omega=${16}
kappa=${17}
input_data_path=${18}
output_data_path=${19}
howtospread=${20}

#シミュレーションを回す
for i in `seq 1 10`
do
    tmp="${output_data_path}/output${i}.dat"
    #シミュレーションにおいて数値解析と同じ結果になったかをフラグとして保持(同じなら0,異なるなら1)
    flag=1
    #数値解析と同じ結果が得られるまでwhileで無限ループ
    while :
    do
        #数値解析と同じ結果が得られたならブレーク
        if [ ${flag} -eq 0 ]; then
            date '+%Y-%m-%d %H:%M:%S'
            echo "Simulation No.${i} successed!"
            break
        fi
        rm -f $tmp
        date '+%Y-%m-%d %H:%M:%S'
        echo "Simulation No.${i} started."
        ../build/a.out $t $n $init_s1 $init_i1 $init_r1 $init_s2 $init_i2 $init_r2 $k $p $graph $interval $m $tau $deltaw $omega $kappa $input_data_path>$tmp
        flag=`../build/judge $howtospread $tmp`
        if [ $flag -eq 1 ]; then
            date '+%Y-%m-%d %H:%M:%S'
            echo "Simulation No.${i} failed. trying again."
        fi
    done
done