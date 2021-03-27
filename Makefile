gconvert: main.o
	g++ main.o -o gconvert --std=c++20

main.o: main.cpp
	g++ -c main.cpp --std=c++20

clean:
	rm *.o gconvert
