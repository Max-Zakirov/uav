CC = g++
CFLAGS = -std=c++17 -Wall

all: server client

server: src/main_server.cpp src/UDPServer.cpp src/CRSF.cpp
	$(CC) $(CFLAGS) -o server src/main_server.cpp src/UDPServer.cpp src/CRSF.cpp

client: src/main_client.cpp src/UDPClient.cpp src/CRSF.cpp
	$(CC) $(CFLAGS) -o client src/main_client.cpp src/UDPClient.cpp src/CRSF.cpp

clean:
	rm -f server client
