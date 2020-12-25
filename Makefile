bin_mpi:
	mpic++ -O0 -g src/main.cpp src/primary.cpp -o bin_mpi -std=c++11

clean:
	rm bin_mpi

report.out:
	g++ src/report/report.cpp -o report.out -std=c++11	

report: primary.out report.out 
	./report.out 2> tmp.txt && rm tmp.txt 

RUN = mpisubmit-new.pl -p
CMD = primary.out 1 100000000 result.txt report/all.dat report/max.dat

reportPolus: primary.out
	$(RUN) 1 $(CMD) && $(RUN) 2 $(CMD) && $(RUN) 4 $(CMD)  && $(RUN) 8 $(CMD) && $(RUN) 16 $(CMD) && $(RUN) 20 $(CMD)

graph:
	sort -nk1 report/all.dat -o report/all.dat  && sort -nk1 report/max.dat -o report/max.dat && gnuplot report/all.plt && gnuplot report/max.plt
