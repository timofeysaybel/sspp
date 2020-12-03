multiply.out:
	mpicxx src/main.cpp src/matrix.cpp -o multiply.out -std=c++98

init.out:
	g++ src/initMatrix.cpp -o init.out -std=c++11

clean:
	rm report/*.dat *.out *.err

report: multiply.out
	python src/report.py

graph:
	gnuplot report/time0.plt && gnuplot report/time1.plt && gnuplot report/time2.plt && gnuplot report/speedup0.plt && gnuplot report/speedup1.plt && gnuplot report/speedup2.plt && gnuplot report/efficiency0.plt && gnuplot report/efficiency1.plt && gnuplot report/efficiency2.plt
