set terminal png
set output "report/max_pthread.png"
set xrange [1:20]
set title "Максимальное время выполнения среди всех процессов для диапазона [1,10^8]"
plot "report/max_pthread.dat" using 1:2 with lines
