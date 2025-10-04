all: dev copy_certs
	./server

dev: server ./share/index
	./server

server: ./src/server.cpp
	g++ -Wall ./src/server.cpp -o server

./share/index: ./src/generate_index.sh
	. ./src/generate_index.sh > share/index

copy_certs:
	sudo mkdir -p /etc/ssl/certs/
	sudo cp -n ./ssl/* /etc/ssl/certs/
	sudo cp -n ./nginx.conf /etc/nginx/conf.d/shinysocks.conf
	sudo nginx -s reload
