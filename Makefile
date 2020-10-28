multiply.out:
	g++ src/test/main.cpp src/matrix/matrix.cpp -o multiply.out
init.out:
	g++ src/test/initMatrix.cpp -o init.out
clean:
	rm *.out

test.out:
	g++ src/test/test.cpp -o test.out
test: multiply.out test.out
	./test.out

