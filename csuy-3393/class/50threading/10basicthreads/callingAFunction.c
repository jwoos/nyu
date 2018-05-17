// How to call a function
#include <pthread.h>
#include <stdio.h>

void *foo(void* arg) {
    fprintf(stderr, "foo(%s)\n", (char*)arg);
}

int main() {

    // #1, directly
    foo("directly");

    // #2, Via a fuction pointer
    void *(*func)(void*);
    func = foo;
    func("from func");
    func = &foo;
    func("from func via address");

    // #3, creating a thread
    pthread_t tid;
    pthread_create(&tid, NULL, foo, "as a thread");
    pthread_join(tid, NULL);
}
