main.out:
	g++ src/matrix/main.cpp src/matrix/matrix.cpp -o main.out -std=c++11
multiply.out:
	g++ src/test/main.cpp src/matrix/matrix.cpp -o multiply.out -std=c++11
init.out:
	g++ src/test/initMatrix.cpp -o init.out -std=c++11
clean:
	rm *.out report/*.dat matrix/*.bin

test.out:
	g++ src/test/test.cpp -o test.out -std=c++11
test: multiply.out test.out
	./test.out
report.out: 
	g++ -L$PAPI_DIR/lib-I$PAPI_DIR/include src/report/report.cpp src/matrix/matrix.cpp -o report.out -lpapi -std=c++11
report: report.out
	./report.out matrix/A matrix/B && gnuplot report/cyc.plt && gnuplot report/l1.plt && gnuplot report/l2.plt && gnuplot report/flop.plt && gnuplot report/clocks.plt
	

