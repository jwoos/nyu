#include "vector.h"


Vector* vectorConstruct(uint64_t cap) {
	Vector* vector = malloc(sizeof(Vector));
	if (vector == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (!cap) {
		cap = DATA_DEFAULT_SIZE;
	}

	vector -> size = 0;
	vector -> capacity = cap;
	vector -> array = calloc(cap, sizeof(void*));
	if (vector -> array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	return vector;
}

void vectorDeconstruct(Vector* vector, void (*fn)(void*)) {
	if (vector == NULL) {
		return;
	}

	for (uint64_t i = 0; i < vector -> capacity; i++) {
		if (vector -> array[i] != NULL) {
			if (fn != NULL) {
				(*fn)(vector -> array[i]);
			}
			vector -> array[i] = NULL;
		}
	}

	free(vector -> array);
	free(vector);
}

void vectorPush(Vector* vector, void* data) {
	if (vector -> size == vector -> capacity) {
		vectorResize(vector, MULTIPLY, DATA_INCREASE_FACTOR, NULL);
	}

	vector -> array[vector -> size] = data;
	vector -> size++;
}

void* vectorPop(Vector* vector) {
	vector -> size--;

	void* data = vector -> array[vector -> size - 1];
	vector -> array[vector -> size] = NULL;

	return data;
}

void* vectorGet(const Vector* vector, uint64_t index) {
	return vector -> array[index];
}

void vectorSet(Vector* vector, uint64_t index, void* data) {
	vector -> array[index] = data;
}

void vectorInsert(Vector* vector, uint64_t index, void* data) {
	if (vector -> size == vector -> capacity) {
		vectorResize(vector, MULTIPLY, DATA_INCREASE_FACTOR, NULL);
	}

	vector -> size++;

	memmove(vector -> array + (index + 1), vector -> array + index, sizeof (void*) * (vector -> size - (index + 1)));

	vectorSet(vector, index, data);
}

void vectorDelete(Vector* vector, uint64_t index, void (*fn)(void*)) {
	if (fn != NULL) {
		(*fn)(vector -> array[index]);
	}
	memmove(vector -> array + index, vector -> array + (index + 1), sizeof (void*) * (vector -> size - (index + 1)));

	vector -> size--;
}

void vectorClear(Vector* vector, void (*fn)(void*)) {
	for (uint64_t i = 0; i < vector -> size - 1; i++) {
		if (fn != NULL) {
			(*fn)(vector -> array[i]);
		}
		vector -> array[i] = NULL;
	}
	vector -> size = 0;
}

void vectorResize(Vector* vector, enum Resize action, uint64_t amount, void (*fn)(void*)) {
	uint64_t currentCapacity = vector -> capacity;
	uint64_t proposedSize;

	bool reduction = false;

	switch (action) {
		case ADD:
			proposedSize = currentCapacity + amount;
			break;

		case MULTIPLY:
			proposedSize = currentCapacity * amount;
			break;

		case SUBTRACT:
			proposedSize = max(currentCapacity - amount, 0);
			reduction = true;
			break;

		case DIVIDE:
			proposedSize = currentCapacity / amount;
			reduction = true;
			break;

		case SET:
			proposedSize = amount;
			reduction = proposedSize < currentCapacity;
			break;
	}

	if (reduction) {
		for (uint64_t i = vector -> size; i < vector -> capacity; i++) {
			(*fn)(vector -> array[i]);
		}
	}

	vector -> capacity = proposedSize;
	vector -> size = min(vector -> capacity, vector -> size);
	vector -> array = realloc(vector -> array, sizeof (*(vector -> array)) * (vector -> capacity));
	if (vector -> array == NULL) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}
}
