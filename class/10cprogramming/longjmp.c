/*
  longjmp.c

  Demonstrates how setjmp / longjmp work. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

void curly() { 
    printf("In curly\n");
    longjmp(buf, 17);
}

void larry() { 
    printf("In larry\n");
    //    longjmp(buf, 42);
    curly();
}

void moe() {
    printf("In moe\n");
    larry();
}

int main() {
    int val = setjmp(buf);
    if (val) {
        printf("Wow! back from a long jump! val = %d\n", val);
    }
    else {
        printf("Established jump buffer\n");
        moe();
    }
}
