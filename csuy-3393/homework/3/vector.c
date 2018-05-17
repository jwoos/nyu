#include "vector.h"


#define DU_DATA_INCREASE_FACTOR 2
#define DU_DATA_DEFAULT_SIZE 16


Vector* vectorConstruct(uint64_t cap) {
	Vector* vector = malloc(sizeof(Vector));
	if (vector == NULL) {
		perrorQuit(PERROR_MEMORY);
	}

	if (!cap) {
		cap = DU_DATA_DEFAULT_SIZE;
	}

	vector -> size = 0;
	vector -> capacity = cap;
	vector -> array = calloc(cap, sizeof(void*));
	if (vector -> array == NULL) {
		perrorQuit(PERROR_MEMORY);
	}

	return vector;
}

void vectorDeconstruct(Vector* vector, void (*fn)(void*)) {
	if (fn == NULL) {
		fn = &free;
	}

	for (uint64_t i = 0; i < vector -> capacity; i++) {
		if (vector -> array[i] != NULL) {
			(*fn)(vector -> array[i]);
			vector -> array[i] = NULL;
		}
	}

	free(vector -> array);
	free(vector);
}

void vectorPush(Vector* vector, void* data) {
	if (vector -> size == vector -> capacity) {
		vectorResize(vector, MULTIPLY, DU_DATA_INCREASE_FACTOR);
	}

	vector -> array[vector -> size] = data;
	vector -> size++;
}

void* vectorPop(Vector* vector) {
	vector -> size--;

	void* data = vector -> array[vector -> size];
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
		vectorResize(vector, MULTIPLY, DU_DATA_INCREASE_FACTOR);
	}

	vector -> size++;

	memmove(vector -> array + (index + 1), vector -> array + index, sizeof (void*) * (vector -> size - (index + 1)));

	vectorSet(vector, index, data);
}

void vectorDelete(Vector* vector, uint64_t index, void (*fn)(void*)) {
	if (fn == NULL) {
		fn = &free;
	}

	(*fn)(vector -> array[index]);
	memmove(vector -> array + index, vector -> array + (index + 1), sizeof (void*) * (vector -> size - (index + 1)));

	vector -> size--;
}

void vectorClear(Vector* vector, void (*fn)(void*)) {
	if (fn == NULL) {
		fn = &free;
	}

	for (uint64_t i = 0; i < vector -> size - 1; i++) {
		(*fn)(vector -> array[i]);
		vector -> array[i] = NULL;
	}
	vector -> size = 0;
}

// FIXME free memory for size reductions
void vectorResize(Vector* vector, enum Resize action, uint64_t amount) {
	uint64_t currentCapacity = vector -> capacity;
	uint64_t proposedSize;

	switch (action) {
		case ADD:
			proposedSize = currentCapacity + amount;
			break;

		case MULTIPLY:
			proposedSize = currentCapacity * amount;
			break;

		case SUBTRACT:
			proposedSize = max(currentCapacity - amount, 0);
			break;

		case DIVIDE:
			proposedSize = currentCapacity / amount;
			break;

		case SET:
			proposedSize = amount;
			break;
	}

	vector -> capacity = proposedSize;
	vector -> size = min(vector -> capacity, vector -> size);
	vector -> array = realloc(vector -> array, sizeof (*(vector -> array)) * (vector -> capacity));
	if (vector -> array == NULL) {
		perrorQuit(PERROR_MEMORY);
	}
}
