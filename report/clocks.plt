set terminal png
set output "report/clocks.png"
set xtics ("ijk 32" 0, "ikj 32" 1,"ikj optimal" 2)
set title "clocks for 1000*1000"
plot "report/clocks.dat" using 1:2 with lines
