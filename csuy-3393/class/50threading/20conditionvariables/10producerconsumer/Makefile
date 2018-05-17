all:	procon_tanenbaum procon_static_initializers

procon_tanenbaum: procon_tanenbaum.c
	gcc -std=c99 procon_tanenbaum.c -o procon_tanenbaum -lpthread

procon_static_initializers: procon_static_initializers.c
	gcc -std=c99 procon_static_initializers.c -o procon_static_initializers -lpthread

clean:
	rm -f procon_tanenbaum procon_static_initializers
