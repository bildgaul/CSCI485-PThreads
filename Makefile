all: threads.c
	gcc -pthread -Wall -o threads threads.c

clean:
	$(RM) threads *~
