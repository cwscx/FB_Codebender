CC = g++

CXXFLAGS= -g -Wall -fpermissive

LDFLAGS= -g

server: server.o

client: client.o

server.o: server.hpp server.cpp

client.o: client.hpp client.cpp

all: server client

clean: rm -rf client server *.o
