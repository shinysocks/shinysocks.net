.SILENT:
all:
	g++ -g server.cpp -o server
	echo compiled
	./server
