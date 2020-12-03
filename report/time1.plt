set terminal png
set output "report/time1.png"
set xtics ("1" 1, "32" 32,"64" 64,"128" 128,"256" 256,"512 default" 512,"512 random" 612)
set title "time for 4096*1024"
plot "report/time1.dat" using 1:2 with lines
