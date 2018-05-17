static const int BUF_SIZE = 10;

typedef struct bounded_buffer {
    int buffer[BUF_SIZE];
    int front;
    int back;
    int size;
} BB;

void init_bb(BB *bb);
void add_bb(BB *bb, int val, bool *success);
int remove_bb(BB *bb, bool *success);
void print_bb(BB *bb);
