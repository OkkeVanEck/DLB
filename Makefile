CC = cc
CFLAGS = -Wall -Wextra -O2
all: client


client: src/client.c src/network.c
	${CC} ${CFLAGS} src/client.c src/network.c -o bin/client.o -lpthread

clean:
	rm -f bin/*.o
