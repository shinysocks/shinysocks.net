all: server ./share/index
	./server

server: ./src/server.cpp
	g++ -Wall ./src/server.cpp -o server

./share/index: ./src/generate_index.sh
	. ./src/generate_index.sh > share/index
