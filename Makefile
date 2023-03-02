all: threads.c threadPLocks.c
	gcc -pthread -Wall -o threads threads.c
	gcc -pthread -Wall -o plocks threadPLocks.c

clean:
	$(RM) threads *~
