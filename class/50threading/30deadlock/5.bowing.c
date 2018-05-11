/*
	Bow / bow back
	Multi-threaded.
	Locks placed within bower struct
	but locking them within the bowing function.

	Original idea from Java Puzzlers
*/

#include <string.h>
#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	// printf
#include <unistd.h>     // sleep

typedef struct {
    char name[20];
    pthread_mutex_t mutex;
} Friend;


void init_friend(Friend* friendP, char* name) {
    strcpy(friendP->name, name);
    pthread_mutex_init(&(friendP->mutex), NULL);
}

void clean_up_friend(Friend* friendP) {
    pthread_mutex_destroy(&(friendP->mutex));
}

void bow_back(Friend* bower, Friend* bowie);

void bow(Friend* bower, Friend* bowie) {
    printf("%s: I bow to %s.\n", bower->name, bowie->name);
    bow_back(bowie, bower);
}

void bow_back(Friend* bower, Friend* bowie) {
    printf("%s: I bow back to %s.\n", bower->name, bowie->name);
}

void* bowing(void* p) {
    Friend** friends = (Friend**)p;
    fprintf(stderr, "Requesting bower: %s\n", friends[0]->name);
    pthread_mutex_lock(&friends[0]->mutex);
    fprintf(stderr, "Acquired bower: %s\n", friends[0]->name);

    fprintf(stderr, "Requesting bowie: %s\n", friends[1]->name);
    pthread_mutex_lock(&friends[1]->mutex);
    fprintf(stderr, "Acquired bowie: %s\n", friends[1]->name);

    bow(friends[0], friends[1]);

    pthread_mutex_unlock(&friends[0]->mutex);
    pthread_mutex_unlock(&friends[1]->mutex);
    return NULL;
}

int main() {
    Friend alphonse;
    init_friend(&alphonse, "Alphonse");
    Friend gaston;
    init_friend(&gaston, "Gaston");
    pthread_t tid1, tid2;

    Friend* ag[] = {&alphonse, &gaston};
    Friend* ga[] = {&gaston, &alphonse};
    pthread_create(&tid1, NULL, bowing, (void*)ag);
    pthread_create(&tid2, NULL, bowing, (void*)ga);

    //  pthread_exit(0);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    clean_up_friend(&alphonse);
    clean_up_friend(&gaston);

}
