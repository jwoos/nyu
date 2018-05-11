#include <stdio.h>
#include <stdbool.h>
#include "bb.h"

void init_bb(BB *bb) {
    bb->front = bb->back = bb->size = 0;
}

void add_bb(BB *bb, int val, bool *success) {
    fprintf(stderr, "Attempting to add %d ", val);
    if (bb->size == BUF_SIZE) {
        if (success) *success = false;
        fprintf(stderr, "failed: %d\n", val);
    } else {
        bb->buffer[bb->back] = val;
        bb->back = ++(bb->back) % BUF_SIZE;
        ++(bb->size);
        if (success) *success = true;
        fprintf(stderr, "succeeded: %d\n", val);
    }
}

int remove_bb(BB *bb, bool *success) {
    fprintf(stderr, "Attempting to remove value. ");
    int result = -1;
    if (bb->size == 0) {
        if (success) *success = false;
        fprintf(stderr, "failed\n");
    } else {
        result = bb->buffer[bb->front];
        bb->front = ++(bb->front) % BUF_SIZE;
        --(bb->size);
        if (success) *success = true;
        fprintf(stderr, "succeeded: %d\n", result);
    }
    return result;
}

void print_bb(BB *bb) {
    for (int count = 0; count < bb->size; ++count) {
        fprintf(stderr, "%d ", bb->buffer[(bb->front + count) % BUF_SIZE]);
    }
    fprintf(stderr, "\n");
}

