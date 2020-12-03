set terminal png
set output "report/speedup1.png"
set format y "10^{%L}"
set xtics ("1" 1, "32" 32,"64" 64,"128" 128,"256" 256,"512 default" 512,"512 random" 612)
set title "SpeedUp for 4096*1024"
plot "report/speedup1.dat" using 1:2 with lines
