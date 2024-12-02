CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lws2_32
OBJ = vcs.o init.o stage.o commit.o network_transfer.o

vcs: $(OBJ)
	$(CC) $(CFLAGS) -o vcs $(OBJ) $(LDFLAGS)

vcs.o: vcs.c init.h stage.h commit.h network_transfer.h
	$(CC) $(CFLAGS) -c vcs.c

init.o: init.c init.h
	$(CC) $(CFLAGS) -c init.c

stage.o: stage.c stage.h
	$(CC) $(CFLAGS) -c stage.c

commit.o: commit.c commit.h
	$(CC) $(CFLAGS) -c commit.c

network_transfer.o: network_transfer.c network_transfer.h
	$(CC) $(CFLAGS) -c network_transfer.c

clean:
	rm -f *.o vcs
