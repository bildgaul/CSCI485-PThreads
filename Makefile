all: threads.c threadPLocks.c
	gcc -pthread -Wall -o threads threads.c
	gcc -pthread -Wall -o plocks threadPLocks.c
	gcc -pthread -Wall -o tasThreads tasThreads.c

clean:
	rm -f threads plocks tasThreads *~
