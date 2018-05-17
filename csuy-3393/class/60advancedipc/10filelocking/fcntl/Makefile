all: lockSomething whoIsLocking filelockingcycle

lockSomething: lockSomething.c
	gcc -Wall -std=c99 -o lockSomething lockSomething.c

whoIsLocking: whoIsLocking.c
	gcc -Wall -std=c99 -o whoIsLocking whoIsLocking.c

filelockingcycle: filelockingcycle.c
	gcc -Wall -std=c99 -o filelockingcycle filelockingcycle.c

clean:
	rm -f  lockSomething whoIsLocking filelockingcycle
