#ifndef DU_DIRECTORY_H
#define DU_DIRECTORY_H

#include <dirent.h>
#include <stdlib.h>

#include "utils.h"
#include "vector.h"


/* A directory is a wrapper for DIR* and holds
 * the name and size
 */
typedef struct Directory {
	char* name;
	int size;
	DIR* dir;
} Directory;

Directory* directoryConstruct(char*, DIR*);

void directoryDeconstruct(Directory*);


#endif
