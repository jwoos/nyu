/* 
	Bow / bow back

   Multi-threaded
*/

#include <stdio.h>      // printf
#include <unistd.h>     // sleep
#include <string.h>     // strcpy
#include <pthread.h> 	// pthread_t, pthread_create

struct Friend {
    char name[20];
};

void init_friend(struct Friend* friend, char* name) {
    strcpy(friend->name, name);
}

void bow_back(struct Friend* bowee, struct Friend* bower) {
    printf("%s: I bow back to %s\n", bowee->name, bower->name);
}

void bow(struct Friend* bower, struct Friend* bowee) {
    printf("%s: I bow to %s\n", bower->name, bowee->name);
    //sleep(1);
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
    struct Friend hubert;
    init_friend(&hubert, "Hubert");

    struct Friend* ag[] = {&alphonse, &gaston};
    pthread_t tid1;
    pthread_create(&tid1, NULL, bowing, (void*)ag);

    // struct Friend* gh[] = {&gaston, &hubert};
    // pthread_t tid2;
    // pthread_create(&tid2, NULL, bowing, (void*)gh);

    // struct Friend* ha[] = {&hubert, &alphonse};
    // pthread_t tid3;
    // pthread_create(&tid3, NULL, bowing, (void*)ha);

    struct Friend* ga[] = {&gaston, &alphonse};
    pthread_t tid4;
    pthread_create(&tid4, NULL, bowing, (void*)ga);
    
    pthread_exit(0);
}
