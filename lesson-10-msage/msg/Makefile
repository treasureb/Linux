.PHONY:all
all:server client

server:server.c common.c
	gcc -g -o $@ $^
client:client.c common.c
	gcc -g -o $@ $^

.PHONY:clean
clean:
	rm -f server client
