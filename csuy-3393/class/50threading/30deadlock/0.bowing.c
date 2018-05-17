/* 
	Bow / bow back
    Single event / single threaded

	Idea from Java Puzzlers, (I think, but now I can't find it...)
*/

#include <stdio.h>
#include <string.h>

struct Friend {
    char name[20];
};

void init_friend(struct Friend* friend, const char* name) {
    strcpy(friend->name, name);
}

void bow_back(struct Friend* bowee, struct Friend* bower) {
    fprintf(stderr, "%s: I bow back to %s\n", bowee->name, bower->name);
}

void bow(struct Friend* bower, struct Friend* bowee) {
    fprintf(stderr, "%s: I bow to %s\n", bower->name, bowee->name);
    bow_back(bowee, bower);
}


int main() {
    struct Friend alphonse;
    init_friend(&alphonse, "Alphonse");
    struct Friend gaston;
    init_friend(&gaston, "Gaston");

    bow(&alphonse, &gaston);
}
