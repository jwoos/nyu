FLAGS = -Wall -std=c99

all: sharedMemCreate sharedMemRead sharedMemUnlink

sharedMemCreate: sharedMemCreate.c
	gcc ${FLAGS} -o sharedMemCreate sharedMemCreate.c #-lrt

sharedMemRead: sharedMemRead.c
	gcc ${FLAGS} -o sharedMemRead sharedMemRead.c #-lrt

sharedMemUnlink: sharedMemUnlink.c
	gcc ${FLAGS} -o sharedMemUnlink sharedMemUnlink.c #-lrt

clean:
	rm -f sharedMemCreate sharedMemRead sharedMemUnlink
