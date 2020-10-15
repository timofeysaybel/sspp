set terminal png
set output "report/graph.png"
set xtics ("ijk" 0,"ikj" 1,"kij" 2,"jik" 3,"jki" 4,"kji" 5)
set title "time for 500*500"
plot "report/data.dat" using 1:2 with lines
