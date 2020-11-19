set terminal png
set output "report/all_pthread.png"
set xrange [1:20]
set title "Суммарное время выполнения для диапазона [1,10^8]"
plot "report/all_pthread.dat" using 1:2 with lines
