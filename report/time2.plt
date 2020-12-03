set terminal png
set output "report/time2.png"
set format y "10^{%L}"
set format x "10^{%L}"
set xtics ("1" 1, "32" 32,"64" 64,"128" 128,"256" 256,"512 default" 512,"512 random" 612)
set title "time for 4096*4096"
plot "report/time2.dat" using 1:2 with lines
