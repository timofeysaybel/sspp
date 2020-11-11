primary.out:
	mpic++ src/main.cpp src/primary.cpp -o primary.out -std=c++11

clean:
	rm *.out

report1.out:
	g++ src/report/report1.cpp -o report1.out -std=c++11

report2.out:
	g++ src/report/report2.cpp -o report2.out -std=c++11	

report: primary.out report1.out report2.out 
	./report1.out && ./report2.out
