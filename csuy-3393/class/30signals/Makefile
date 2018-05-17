#  _BSD_SOURCE is needed to enable "BSD semantics" for signal,
#  i.e. keeping the handler on after using.

#  The man page for signal says that _BSD_SOURCE is defined by
#  default, but that's not true if we use c99.

FLAGS = -std=c99 -Wall -D _XOPEN_SOURCE -D _BSD_SOURCE
FLAGS_NO_BSD = -std=c99 -Wall -D _XOPEN_SOURCE #  -D _BSD_SOURCE
#FLAGS = -std=c99 -Wall -D _POSIX_C_SOURCE=1

all: sigdemo0 sigdemo1 sigdemo2 patricide sigdemo1_no_bsd patricide_twice

sigdemo0: sigdemo0.c
	gcc ${FLAGS} -o sigdemo0 sigdemo0.c

sigdemo1: sigdemo1.c
	gcc ${FLAGS} -o sigdemo1 sigdemo1.c

sigdemo1_no_bsd: sigdemo1.c
	gcc ${FLAGS_NO_BSD} -o sigdemo1_no_bsd sigdemo1.c

sigdemo2: sigdemo2.c
	gcc ${FLAGS} -o sigdemo2 sigdemo2.c

patricide: patricide.c
	gcc ${FLAGS} -o patricide patricide.c

patricide_twice: patricide_twice.c
	gcc ${FLAGS} -o patricide_twice patricide_twice.c

clean:
	rm -f sigdemo0 sigdemo1 sigdemo2 sigdemo1_no_bsd \
	      patricide patricide_twice
