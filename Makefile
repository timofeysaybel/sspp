primary.out:
	mpic++ src/main.cpp src/primary.cpp -o primary.out -std=c++11

clean:
	rm *.out *.txt report/*.dat *.err

report.out:
	g++ src/report/report.cpp -o report.out -std=c++11	

report: primary.out report.out 
	./report.out 2> tmp.txt && rm tmp.txt && gnuplot report/all.plt && gnuplot report/max.plt

RUN = mpisubmit-new.pl -p
CMD = primary.out 1 1000000 result.txt report/all.dat report/max.dat

reportPolus: primary.out
	$(RUN) 1 $(CMD) && $(RUN) 2 $(CMD) && $(RUN) 4 $(CMD)  && $(RUN) 8 $(CMD) && $(RUN) 16 $(CMD) && $(RUN) 20 $(CMD)

graph:
	gnuplot report/all.plt && gnuplot report/max.plt
