all: barrierTest

barrierTest: barrier.c barrier.h barrierTest.c 
	gcc -Wall -std=c99 -o barrierTest barrier.c barrierTest.c -lpthread

clean:
	rm -f barrierTest
