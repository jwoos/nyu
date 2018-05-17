all: setUp produce destroy display consume produce2 produce3

setUp: bb.c setUp.c
	gcc -std=c99 -o setUp setUp.c bb.c

destroy: destroy.c
	gcc -std=c99 -o destroy destroy.c

display: display.c  bb.c
	gcc -std=c99 -o display display.c bb.c

produce: bb.c produce.c
	gcc -std=c99 -o produce produce.c bb.c

produce2: bb.c produce2.c
	gcc -std=c99 -o produce2 produce2.c bb.c

produce3: bb.c produce3.c
	gcc -std=c99 -o produce3 produce3.c bb.c

consume: bb.c consume.c
	gcc -std=c99 -o consume consume.c bb.c

clean:
	rm -f setUp produce destroy display consume produce2 produce3
