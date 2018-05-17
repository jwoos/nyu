#include "path.h"


Path* pathConstruct(void) {
	Path* path = malloc(sizeof(*path));

	path -> directories = vectorConstruct(16);

	path -> accounted = vectorConstruct(16);

	return path;
}

void pathDeconstruct(Path* path) {
	vectorDeconstruct(path -> directories, directoryDeconstruct);

	vectorDeconstruct(path -> accounted, NULL);

	free(path);
}

void pathPush(Path* path, Directory* dir) {
	vectorPush(path -> directories, dir);
}

Directory* pathPop(Path* path) {
	if (path -> directories -> size == 0) {
		return NULL;
	}
	return vectorPop(path -> directories);
}

Directory* pathParent(Path* path) {
	return vectorGet(path -> directories, path -> directories -> size - 2);
}

Directory* pathCurrent(Path* path) {
	if (path -> directories -> size == 0) {
		return NULL;
	}
	return vectorGet(path -> directories, path -> directories -> size - 1);
}

char* pathBuild(Path* path) {
	int size = 0;

	for (int i = 0; i < path -> directories -> size; i++) {
		Directory* directory = vectorGet(path -> directories, i);
		size += strlen(directory -> name);
		size++;
	}

	char* relative = malloc(sizeof(char) * size);

	int index = 0;
	for (int i = 0; i < path -> directories -> size; i++) {
		Directory* directory = vectorGet(path -> directories, i);
		int length = strlen(directory -> name);
		strncpy(relative + index, directory -> name, length);
		index += length;
		if (i != path -> directories -> size - 1) {
			relative[index] = '/';
			index++;
		}
	}
	relative[index] = '\0';

	return relative;
}
