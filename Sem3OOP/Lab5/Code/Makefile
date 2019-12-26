solution: main.o figure.o stack.o
	g++ -std=c++14 main.o figure.o stack.o -o solution

main.o: ./Src/main.cpp
	g++ -c ./Src/main.cpp

figure.o: ./Src/figure.cpp
	g++ -c ./Src/figure.cpp

stack.o: ./Src/stack.cpp
	g++ -c ./Src/stack.cpp

clean:
	rm -f *.o *.a solution