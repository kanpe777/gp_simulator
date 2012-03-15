#!/bin/sh

#------ gnuplot 出力用スクリプトサンプル

#echo cd ..

# 出力画像の形式を設定．EPS の場合は 'set terminal postscript eps'
echo 'set terminal postscript eps color' > model.gnuplot

# 出力ファイル名を決定
echo 'set output "point_change_graph.eps"' >> model.gnuplot

# グラフのタイトルを設定
#echo 'set title "A parabolic orbit"' >> model.gnuplot

# x軸のラベルを設定
echo 'set xlabel "x Generation"' >> model.gnuplot

# y軸のラベルを設定
echo 'set ylabel "y Point"' >> model.gnuplot
#echo 'set ylabel "y distance"' >> model.gnuplot
#echo 'set ylabel "ydiff"' >> model.gnuplot

# x軸の範囲を指定
echo 'set xrange [0:200] ' >> model.gnuplot


# y軸に2カラム目，x軸に1カラム目をプロット
# using 1列目(x): 2列目(y)
echo 'plot "change_graph.txt" using 1:2 title "change_Point" with line' >> model.gnuplot
#echo 'plot "centroid-tripyramid-author.txt" using 1:(sqrt(($2*$2)+($3*$3))) title "the_center_of_gravity" with line' >> model.gnuplot
#「,」(カンマ)で区切ると、同じグラフの中に、二本以上の線可能
#echo 'plot "centroid-tripyramid-author.txt" using 1:(sqrt(($2*$2)+($3*$3))) title "tripyramid" with line,"centroid-pushGround-author.txt" using 1:(sqrt(($2*$2)+($3*$3))) title "pushGround" with line,"centroid-guntank-author.txt" using 1:(sqrt(($2*$2)+($3*$3))) title "guntank" with line' >> model.gnuplot
#echo 'plot "centroidDiff-tripyramid-author.txt" using 1:3 title "the_center_of_gravity_diff" with line' >> model.gnuplot

gnuplot < model.gnuplot
open point_change_graph.eps
rm model.gnuplot
#cd mymodels

#------ end for gnuplot
