:<<'#COMMENTOUT'

#COMMENTOUT

n=1000
m=20

#cmakeでビルド，コンパイル 
cmake -S ../source -B ../build
cmake --build ../build

../build/build_BA_model $n $m
