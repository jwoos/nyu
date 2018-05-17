/*
  6.bowingV3.c
  Bow / bow back
  Multi-threaded.
  Order locks.

  Here the ordering can conveniently be on the addresses of the
  Friends.

  Original idea from Java Puzzlers
*/


#include <string.h>
#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	    // printf

typedef struct {
    char name[20];
    pthread_mutex_t mutex;
} Friend;

void init_friend(Friend* friendP, char* name) {
    strcpy(friendP->name, name);
    pthread_mutex_init(&(friendP->mutex), NULL);
}

void bow_back(Friend* bower, Friend* bowie);

void bow(Friend* bower, Friend* bowie) {
    void bow_back(Friend* bower, Friend* bowie);
    printf("%s: I bow to %s.\n", bower->name, bowie->name);
    bow_back(bowie, bower);
}

void bow_back(Friend* bower, Friend* bowie) {
    printf("%s: I bow back to %s.\n", bower->name, bowie->name);
}

void* bowing(void* p) {
    //  printf("In bowing\n");
    Friend** friends = (Friend**)p;
    if (friends[0] < friends[1]) { // Comparing address of friend objects.
        pthread_mutex_lock(&friends[0]->mutex);
        pthread_mutex_lock(&friends[1]->mutex);
        bow(friends[0], friends[1]);
        pthread_mutex_unlock(&friends[1]->mutex);
        pthread_mutex_unlock(&friends[0]->mutex);
    }
    else if (friends[0] > friends[1]) {
        pthread_mutex_lock(&friends[1]->mutex);
        pthread_mutex_lock(&friends[0]->mutex);
        bow(friends[0], friends[1]);
        pthread_mutex_unlock(&friends[0]->mutex);
        pthread_mutex_unlock(&friends[1]->mutex);
    }
    else { // Tie?  Ok, odd here as you can only tie with yourself...
        pthread_mutex_lock(&friends[0]->mutex);
        bow(friends[0], friends[1]);
        pthread_mutex_unlock(&friends[0]->mutex);
    }
    return NULL;
}

int main() {
    Friend alphonse;
    init_friend(&alphonse, "Alphonse");
    Friend gaston;
    init_friend(&gaston, "Gaston");
    pthread_t tid1, tid2, tid3;

    Friend* ag[] = {&alphonse, &gaston};
    Friend* ga[] = {&gaston, &alphonse};
    Friend* gg[] = {&gaston, &gaston};
    pthread_create(&tid1, NULL, bowing, (void*)ag);
    pthread_create(&tid2, NULL, bowing, (void*)ga);
    pthread_create(&tid3, NULL, bowing, (void*)gg);
    //  pthread_exit(NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
}
