Use make to compile the code. Then run ./threads to run the program without synchronization, ./plocks to run the program with Pthread Lock synchronization, or ./tasLocks to run the program with Test-and-Set Lock synchronization.
The default number of threads is 4. To change this, use the -x argument followed by the desired amount of threads.
The default number of increments per thread is 10,000. To change this, use the -y argument followed by the desired increments per thread.
