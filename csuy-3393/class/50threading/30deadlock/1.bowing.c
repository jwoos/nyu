/* 
   1.bowing.c
   Bow / bow back

   Multi-threaded
*/

#include <stdio.h>      // printf
#include <string.h>     // strcpy
#include <pthread.h> 	// pthread_t, pthread_create

struct Friend {
    char name[20];
};

void init_friend(struct Friend* friend, char* name) {
    strcpy(friend->name, name);
}

void bow_back(struct Friend* bowee, struct Friend* bower) {
    fprintf(stderr, "%s: I bow back to %s\n", bowee->name, bower->name);
}

void bow(struct Friend* bower, struct Friend* bowee) {
    fprintf(stderr, "%s: I bow to %s\n", bower->name, bowee->name);
    bow_back(bowee, bower);
}

void* bowing(void* p) {
    struct Friend** friends = (struct Friend**)p;
    bow(friends[0], friends[1]);
    return NULL;
}

int main() {
    struct Friend alphonse;
    init_friend(&alphonse, "Alphonse");
    struct Friend gaston;
    init_friend(&gaston, "Gaston");

    struct Friend* ag[] = {&alphonse, &gaston};
    pthread_t tid;
    pthread_create(&tid, NULL, bowing, (void*)ag);

    pthread_join(tid, NULL);
    fprintf(stderr, "Done\n");
}
