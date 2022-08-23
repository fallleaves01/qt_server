main: main.cpp encoding.o ./Network/scanner.hpp ./Utilities/worklog.hpp
	g++ -o main main.cpp encoding.o -lpthread -Wall -std=c++17
debug: main.cpp encoding.o ./Network/scanner.hpp ./Utilities/worklog.hpp
	g++ -o main main.cpp encoding.o -lpthread -Wall -std=c++17 -g

encoding.o: ./DataModel/encoding.cpp ./DataModel/encoding.h
	g++ -c ./DataModel/encoding.cpp

clear:
	rm encoding.o main