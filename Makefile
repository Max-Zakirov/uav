CC = g++
CFLAGS = -std=c++17 -Wall

all: server client

server: src/main_server.cpp src/UDPServer.cpp src/SBUS.cpp
	$(CC) $(CFLAGS) -o server src/main_server.cpp src/UDPServer.cpp src/SBUS.cpp

client: src/main_client.cpp src/UDPClient.cpp src/SBUS.cpp
	$(CC) $(CFLAGS) -o client src/main_client.cpp src/UDPClient.cpp src/SBUS.cpp

clean:
	rm -f server client
