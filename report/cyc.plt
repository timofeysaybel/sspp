set terminal png
set output "report/cyc.png"
set xtics ("ijk 32" 0, "ikj 32" 1,"ikj optimal" 2)
set title "cyc for 1000*1000"
plot "report/cyc.dat" using 1:2 with lines
