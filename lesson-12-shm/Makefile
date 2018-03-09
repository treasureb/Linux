.PHONY:all
all:client server

client:client.c common.c
	gcc $^ -g -o $@
server:server.c common.c
	gcc $^ -g -o $@

.PHONY:clean
clean:
	rm -f client server
