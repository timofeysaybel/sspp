set terminal png
set output "report/speedup2.png"
set xtics ("1" 1, "32" 32,"64" 64,"128" 128,"256" 256,"512 default" 512,"512 random" 612)
set title "SpeedUp for 4096*4096"
plot "report/speedup2.dat" using 1:2 with lines
