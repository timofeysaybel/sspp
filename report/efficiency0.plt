set terminal png
set output "report/efficiency0.png"
set xtics ("1" 1, "32" 32,"64" 64,"128" 128,"256" 256,"512 default" 512,"512 random" 612)
set title "Efficiency for 1024*4096"
plot "report/efficiency0.dat" using 1:2 with lines
