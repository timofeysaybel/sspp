set terminal png
set output "report/l1.png"
set xtics ("ijk 32" 0, "ikj 32" 1,"ikj optimal" 2)
set title "l1 for 1000*1000"
plot "report/l1.dat" using 1:2 with lines
