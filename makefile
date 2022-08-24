main: main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ClientMessage.o ClientRequest.o ./Network/scanner.h ./Utilities/worklog.hpp
	g++ -o main main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ClientMessage.o ClientRequest.o -l pthread -l sqlite3 -Wall -std=c++17
debug: main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ClientMessage.o ClientRequest.o ./Network/scanner.h ./Utilities/worklog.hpp
	g++ -o main main.cpp encoding.o Database.o GroupInfo.o UserInfo.o ChatMessage.o SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ClientMessage.o ClientRequest.o -l pthread -l sqlite3 -Wall -std=c++17 -g

encoding.o: ./DataModel/encoding.cpp ./DataModel/encoding.h
	g++ -c ./DataModel/encoding.cpp -Wall -g

Database.o: ./DataBase/Database.cpp ./DataBase/Database.h
	g++ -c ./DataBase/Database.cpp -Wall -g

GroupInfo.o: ./DataBase/GroupInfo.cpp ./DataBase/GroupInfo.h
	g++ -c ./DataBase/GroupInfo.cpp -Wall -g

UserInfo.o: ./DataBase/UserInfo.cpp ./DataBase/UserInfo.h
	g++ -c ./DataBase/UserInfo.cpp -Wall -g

ChatMessage.o: ./DataBase/ChatMessage.cpp ./DataBase/ChatMessage.h
	g++ -c ./DataBase/ChatMessage.cpp -Wall -g

SocketClient.o: ./Network/SocketClient.cpp ./Network/scanner.h
	g++ -c ./Network/SocketClient.cpp -Wall -g

SocketScanner.o: ./Network/SocketScanner.cpp ./Network/scanner.h
	g++ -c ./Network/SocketScanner.cpp -Wall -g

ClientOperate.o: ./Network/ClientOperate.cpp ./Network/scanner.h
	g++ -c ./Network/ClientOperate.cpp -Wall -g

ClientLogin.o: ./Network/ClientLogin.cpp ./Network/scanner.h
	g++ -c ./Network/ClientLogin.cpp -Wall -g

ClientMessage.o: ./Network/ClientMessage.cpp ./Network/scanner.h
	g++ -c ./Network/ClientMessage.cpp -Wall -g

ClientRequest.o: ./Network/ClientRequest.cpp ./Network/scanner.h
	g++ -c ./Network/ClientRequest.cpp -Wall -g

clear:
	rm *.o main