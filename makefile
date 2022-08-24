main: main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ./Network/scanner.h ./Utilities/worklog.hpp
	g++ -o main main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o -l pthread -l sqlite3 -Wall -std=c++17

debug: main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ./Network/scanner.h ./Utilities/worklog.hpp
	g++ -o main main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o -l pthread -l sqlite3 -Wall -std=c++17 -g

encoding.o: ./DataModel/encoding.cpp ./DataModel/encoding.h
	g++ -c ./DataModel/encoding.cpp

Database.o: ./DataBase/Database.cpp ./DataBase/Database.h
	g++ -c ./DataBase/Database.cpp

GroupInfo.o: ./DataBase/GroupInfo.cpp ./DataBase/GroupInfo.h
	g++ -c ./DataBase/GroupInfo.cpp

UserInfo.o: ./DataBase/UserInfo.cpp ./DataBase/UserInfo.h
	g++ -c ./DataBase/UserInfo.cpp

ChatMessage.o: ./DataBase/ChatMessage.cpp ./DataBase/ChatMessage.h
	g++ -c ./DataBase/ChatMessage.cpp

SocketClient.o: ./Network/SocketClient.cpp ./Network/scanner.h
	g++ -c ./Network/SocketClient.cpp

SocketScanner.o: ./Network/SocketScanner.cpp ./Network/scanner.h
	g++ -c ./Network/SocketScanner.cpp

ClientOperate.o: ./Network/ClientOperate.cpp ./Network/scanner.h
	g++ -c ./Network/ClientOperate.cpp

ClientLogin.o: ./Network/ClientLogin.cpp ./Network/scanner.h
	g++ -c ./Network/ClientLogin.cpp

clear:
	rm *.o main