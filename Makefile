primary.out:
	mpic++ src/main.cpp src/primary.cpp -o primary.out -std=c++11

primaryPthread.out:
	mpic++ src/mainPthread.cpp src/primary.cpp -o primaryPthread.out -std=c++11 -lpthread

clean:
	rm *.out *.txt report/*.dat *.err

report.out:
	g++ src/report/report.cpp -o report.out -std=c++11	

report: primary.out report.out 
	./report.out 2> tmp.txt && rm tmp.txt 

RUN = mpisubmit-new.pl -p
CMD = primary.out 1 100000000 result.txt report/all.dat report/max.dat

CMD1 = ./primaryPthread.out 1 100000000 resultPthread.txt report/all_pthread.dat report/max_pthread.dat

reportPolus: primary.out
	$(RUN) 1 $(CMD) && $(RUN) 2 $(CMD) && $(RUN) 4 $(CMD)  && $(RUN) 8 $(CMD) && $(RUN) 16 $(CMD) && $(RUN) 20 $(CMD)

graph:
	sort -nk1 report/all.dat -o report/all.dat  && sort -nk1 report/max.dat -o report/max.dat && gnuplot report/all.plt && gnuplot report/max.plt

reportPthread: primaryPthread.out
	$(CMD1) 1 && $(CMD1) 2 && $(CMD1) 4  && $(CMD1) 8 && $(CMD1) 16 && $(CMD1) 20

graphPthread:
	gnuplot report/all_pthread.plt && gnuplot report/max_pthread.plt
