set terminal png
set output "report/speedup0.png"

set xtics ("1" 1, "32" 32,"64" 64,"128" 128,"256" 256,"512 default" 512,"512 random" 612)
set title "SpeedUp for 1024*4096"
plot "report/speedup0.dat" using 1:2 with linespoints linecolor 2 pointtype 7 pointsize 2
