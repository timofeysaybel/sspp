.PHONY: report

multiply:
	g++ src/matrix/main.cpp src/matrix/matrix.cpp src/matrix/multiplier.cpp -o multiply.out 

init:
	g++ src/test/initMatrix.cpp -o init.out

test:
	make multiply && g++ src/test/test.cpp src/matrix/matrix.cpp -o test.out && ./test.out

report: 
	g++ src/test/report.cpp -o report.out && ./report.out > report/data.dat && gnuplot report/graph.plt
