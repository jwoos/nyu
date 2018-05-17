#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void myHandler(int signalNum) {
    signal( SIGQUIT, myHandler );
    puts("I won't quit!!!");
}

int main() {
    signal( SIGINT, SIG_IGN );
    signal( SIGQUIT, myHandler );

    puts("You can't stop me!");
    while (1) {
	puts("Haha!!!");
	sleep(1);
    }
}
