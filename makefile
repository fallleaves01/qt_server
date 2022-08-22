main: main.cpp encoding.o
	g++ -o main main.cpp encoding.o -lpthread -Wall -std=c++17
debug: main.cpp encoding.o
	g++ -o main main.cpp encoding.o -lpthread -Wall -std=c++17 -g

encoding.o: encoding.cpp encoding.h
	g++ -c encoding.cpp

clear:
	rm encoding.o main