.SILENT:
all:
	. ./src/generate_index.sh > share/index
	g++ -Wall ./src/server.cpp -o server
	./server
	rm server
