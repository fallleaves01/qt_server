main: main.cpp
	g++ main.cpp -o main -lpthread -Wall -std=c++17
debug: main.cpp
	g++ main.cpp -o main -lpthread -Wall -std=c++17 -g
