database = Database.o GroupInfo.o UserInfo.o ChatMessage.o
datamodel = encoding.o
network = SocketClient.o SocketScanner.o ClientOperate.o ClientLogin.o ClientMessage.o ClientRequest.o

dataModel_hpp = ./DataModel/DataAddFriend.hpp ./DataModel/DataGetFriend.hpp ./DataModel/DataGetGroup.hpp \
./DataModel/DataGroup.hpp ./DataModel/DataLogin.hpp ./DataModel/Message.hpp

main: $(database) $(datamodel) $(network)
	g++ $(database) $(datamodel) $(network) main.cpp -o main -Wall -std=c++17 -lpthread -lsqlite3

debug: $(database) $(datamodel) $(network)
	g++ $(database) $(datamodel) $(network) main.cpp -o main -Wall -std=c++17 -lpthread -lsqlite3 -g

Database.o: ./DataBase/Database.cpp ./DataBase/Database.h
	g++ -c ./DataBase/Database.cpp -Wall -g

GroupInfo.o: ./DataBase/GroupInfo.cpp ./DataBase/GroupInfo.h
	g++ -c ./DataBase/GroupInfo.cpp -Wall -g

UserInfo.o: ./DataBase/UserInfo.cpp ./DataBase/UserInfo.h
	g++ -c ./DataBase/UserInfo.cpp -Wall -g

ChatMessage.o: ./DataBase/ChatMessage.cpp ./DataBase/ChatMessage.h
	g++ -c ./DataBase/ChatMessage.cpp -Wall -g

encoding.o: ./DataModel/encoding.cpp ./DataModel/encoding.h $(dataModel_hpp)
	g++ -c ./DataModel/encoding.cpp -Wall -g

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

ClientRequest.o: ./Network/scanner.h
	g++ -c ./Network/ClientRequest.cpp -Wall -g

clear:
	rm *.o main
