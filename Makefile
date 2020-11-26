multiply.out:
	mpic++ src/main.cpp src/matrix.cpp -o multiply.out -std=c++11

clean:
	rm report/*.dat *.out 
