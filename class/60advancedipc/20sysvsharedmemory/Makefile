FLAGS = -Wall -std=c99 -D _XOPEN_SOURCE

all: testSharedMemoryCreate testSharedMemoryRead testSharedMemoryFree

testSharedMemoryCreate: testSharedMemoryCreate.c
	gcc testSharedMemoryCreate.c ${FLAGS} -o testSharedMemoryCreate

testSharedMemoryRead: testSharedMemoryRead.c
	gcc testSharedMemoryRead.c ${FLAGS} -o testSharedMemoryRead

testSharedMemoryFree: testSharedMemoryFree.c
	gcc testSharedMemoryFree.c ${FLAGS} -o testSharedMemoryFree

clean: 
	rm -f testSharedMemoryCreate testSharedMemoryRead testSharedMemoryFree
