FLAGS = -Wall -std=c99

all:	0.bowing 1.bowing 2.bowing 3.bowing 4.bowing 5.bowing 6.bowingV1 6.bowingV2 6.bowingV3


0.bowing:	0.bowing.c
	gcc ${FLAGS} -o 0.bowing 0.bowing.c

1.bowing:	1.bowing.c
	gcc ${FLAGS} -o 1.bowing 1.bowing.c -lpthread

2.bowing:	2.bowing.c
	gcc ${FLAGS} -o 2.bowing 2.bowing.c -lpthread

3.bowing:	3.bowing.c
	gcc ${FLAGS} -o 3.bowing 3.bowing.c -lpthread

4.bowing:   4.bowing.c
	gcc ${FLAGS} -o 4.bowing 4.bowing.c -lpthread

5.bowing: 	5.bowing.c
	gcc ${FLAGS} -o 5.bowing 5.bowing.c -lpthread

6.bowingV1:	6.bowingV1.c
	gcc ${FLAGS} -o 6.bowingV1 6.bowingV1.c -lpthread

6.bowingV2:	6.bowingV2.c
	gcc ${FLAGS} -o 6.bowingV2 6.bowingV2.c -lpthread

6.bowingV3:	6.bowingV3.c
	gcc ${FLAGS} -o 6.bowingV3 6.bowingV3.c -lpthread

clean:
	rm -f 0.bowing 1.bowing 2.bowing 3.bowing 4.bowing 5.bowing 6.bowing 6.bowingV1 6.bowingV2 6.bowingV3
