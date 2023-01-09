<<'#COMMENTOUT'
自立進化型ボットネットのnode-base-SIRSモデルの確率論的シミュレータ
指定した回数だけシミュレーションを行い，感染が拡大したシミュレーションの平均を取る
シミュレーションで用いる初期パラメータをnumerical_analytics_param_list.txtから一行ずつ読み取り
パイプでxargsコマンドに渡す
xargsコマンドは標準入力やファイルからリストを読み込み，コマンドラインを作成して実行するコマンド
(わからなかったらhttps://atmarkit.itmedia.co.jp/ait/articles/1801/19/news014.html を参照)
-L 1 でパイプで渡された1行ごとにコマンドラインを実行
-P 1 で同時に実行するコマンドライン数を1に設定する
#COMMENTOUT

sed '/^#/d' ./numerical_analytics_param_list.txt | xargs -L 1 -P 1 ./parallel.sh