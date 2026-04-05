CC = gcc
CFLAGS = -Wall -g

procmon: procmon.c
	$(CC) $(CFLAGS) -o procmon procmon.c

clean:
	rm -f procmon

