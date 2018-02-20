#ifndef DU_PATH_H
#define DU_PATH_H

#include "directory.h"
#include "utils.h"
#include "vector.h"


/* A path holds a stack of directories as well as the hardlinks
 * already counted
 */
typedef struct Path {
	// vector of Directory*
	Vector* directories;

	// vector of ino_t*
	Vector* accounted;
} Path;

Path* pathConstruct(void);

void pathDeconstruct(Path*);

void pathPush(Path*, Directory*);

Directory* pathPop(Path*);

Directory* pathParent(Path* path);

Directory* pathCurrent(Path* path);

char* pathBuild(Path* path);


#endif
