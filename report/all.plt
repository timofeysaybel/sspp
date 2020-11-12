set terminal png
set output "report/all.png"
set xrange [1:20]
set title "Суммарное время выполнения для диапазона [1,10^7]"
plot "report/all.dat" using 1:2 with lines
