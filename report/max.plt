set terminal png
set output "report/max.png"
set xrange [1:20]
set title "Максимальное время выполнения среди всех процессов для диапазона [1,10^7]"
plot "report/max.dat" using 1:2 with lines
