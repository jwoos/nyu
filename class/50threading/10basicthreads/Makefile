FLAGS =  -std=c99 -Wall

all: t0 t1 t1b t2 t3 t4 t5 t6 t7 t8

t0:	t0.c
	gcc ${FLAGS} t0.c -o t0 

t1:	t1.c
	gcc ${FLAGS} t1.c -o t1 -lpthread

t1b:	t1b.c
	gcc ${FLAGS} t1b.c -o t1b -lpthread

t2:	t2.c
	gcc -std=c99 -Wall t2.c -o t2 -lpthread

t3:	t3.c
	gcc -std=c99 -Wall t3.c -o t3 -lpthread

t4:	t4.c
	gcc -std=c99 -Wall t4.c -o t4 -lpthread

t5:	t5.c
	gcc -std=c99 -Wall t5.c -o t5 -lpthread

t6:	t6.c
	gcc -std=c99 -Wall t6.c -o t6 -lpthread

t7:	t7.c
	gcc -std=c99 -Wall t7.c -o t7 -lpthread

t8:	t8.c
	gcc -std=c99 -Wall t8.c -o t8 -lpthread

clean:
	rm -f  t0 t1 t1b t2 t3 t4 t5 t6 t7 t8

