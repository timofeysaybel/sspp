primary.out:
	g++ src/mainPthread.cpp src/primary.cpp -o primary.out -std=c++11 -lpthread

clean:
	rm *.out *.txt report/*.dat *.err

CMD1 = ./primary.out 1 100000000 resultPthread.txt report/all_pthread.dat report/max_pthread.dat

report: primary.out
	$(CMD1) 1 && $(CMD1) 2 && $(CMD1) 4  && $(CMD1) 8 && $(CMD1) 16 && $(CMD1) 20

graph:
	gnuplot report/all_pthread.plt && gnuplot report/max_pthread.plt
