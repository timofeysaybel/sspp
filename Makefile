.PHONY: report

test: multiply.out test.out 
	./test.out

multiply.out:
	g++ src/matrix/main.cpp src/matrix/matrix.cpp src/matrix/multiplier.cpp -o multiply.out 

init.out:
	g++ src/test/initMatrix.cpp -o init.out

test.out: 
	g++ src/test/test.cpp src/matrix/matrix.cpp -o test.out 

report.out: 
	g++ src/test/report.cpp -o report.out

report/data.dat:
	./report.out > report/data.dat

report: multiply.out report.out report/data.dat
	gnuplot report/graph.plt

clean:
	rm *.out report/data.dat
