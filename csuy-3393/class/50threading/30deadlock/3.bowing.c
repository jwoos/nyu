/* 
	Bow / bow back

   Multi-threaded with mutex
*/

#include <stdio.h>      // printf
#include <string.h>     // strcpy
#include <pthread.h> 	// pthread_t, pthread_create

struct Friend {
    char name[20];
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void init_friend(struct Friend* friend, char* name) {
    strcpy(friend->name, name);
}

void bowBack(struct Friend* bowee, struct Friend* bower) {
    printf("%s: I bow back to %s\n", bowee->name, bower->name);
}

void bow(struct Friend* bower, struct Friend* bowee) {
    printf("%s: I bow to %s\n", bower->name, bowee->name);
    bowBack(bowee, bower);
}

void* bowing(void* p) {
    struct Friend** friends = (struct Friend**)p;
    pthread_mutex_lock(&mutex);
    bow(friends[0], friends[1]);
    pthread_mutex_unlock(&mutex);
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

    struct Friend* ga[] = {&gaston, &alphonse};
    pthread_t tid2;
    pthread_create(&tid2, NULL, bowing, (void*)ga);

    struct Friend* ha[] = {&hubert, &alphonse};
    pthread_t tid3;
    pthread_create(&tid3, NULL, bowing, (void*)ha);

    
    pthread_exit(0);
}
