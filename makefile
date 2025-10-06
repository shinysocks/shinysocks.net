all: server share/index
	./server

server: src/server.cpp
	g++ -Wall src/server.cpp -o server

share/index: src/generate_index.sh
	. ./src/generate_index.sh > share/index

clean:
	rm server server.log* share/index


# cron auto recovery for my server which is ssh tunneled out of a dorm room

# if website returns an error code, re-establish tunnel with aws
#	* * * * * curl -Isf shinysocks.net || /usr/bin/ssh -fNR 8888:localhost:8888 aws 
# 	@reboot sleep 5 && cd /home/shinysocks/shinysocks.net/ && make 
