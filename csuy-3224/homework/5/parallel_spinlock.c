/* Running the mutex with 10 threads yield insertion of 0.009561 seconds
 * running with the spinlock with 10 threads yield insertion of 0.011670 seconds
 * Subsequent runs yieled errors of up to +0.03 seconds so it's well within
 * the error range - and it makes sense that they are both around the same time.
 * The concept of both is to be a blocking call it's just that the spinlock runs
 * through meaningless CPU cycles while the mutex doesn't so in terms of time taken
 * it should not differ much if at all.
 */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


#define NUM_BUCKETS 5     // Buckets in hash table
#define NUM_KEYS 100000   // Number of keys inserted per thread


int num_threads = 1;      // Number of threads (configurable)
int keys[NUM_KEYS];

typedef struct _bucket_entry {
	int key;
	int val;
	struct _bucket_entry* next;
} bucket_entry;

bucket_entry* table[NUM_BUCKETS];
pthread_spinlock_t lock;
pthread_spinlock_t readerLock;
int readers;

void panic(char *msg) {
	printf("%s\n", msg);
	exit(1);
}

double now() {
	struct timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// Inserts a key-value pair into the table
void insert(int key, int val) {
	int i = key % NUM_BUCKETS;
	bucket_entry* e = malloc(sizeof (bucket_entry));

	if (!e) {
		panic("No memory to allocate bucket!");
	}

	/* we want to lock the whole thing as we might grab
	 * the same table[i] if there's another insertion
	 * and end up with an overwrite
	 */
	pthread_spin_lock(&lock);
	e -> next = table[i];
	e -> key = key;
	e -> val = val;
	table[i] = e;
	pthread_spin_unlock(&lock);
}

// Retrieves an entry from the hash table by key
// Returns NULL if the key isn't found in the table
bucket_entry * retrieve(int key) {
	bucket_entry *b;

	pthread_spin_lock(&readerLock);
	readers++;
	if (readers == 1) {
		pthread_spin_lock(&lock);
	}
	pthread_spin_unlock(&readerLock);

	for (b = table[key % NUM_BUCKETS]; b != NULL; b = b -> next) {
		if (b -> key == key) {
			return b;
		}
	}

	pthread_spin_lock(&readerLock);
	readers--;
	if (readers == 0) {
		pthread_spin_unlock(&lock);
	}
	pthread_spin_unlock(&readerLock);

	return NULL;
}

void* put_phase(void *arg) {
	long tid = (long) arg;
	int key = 0;

	// If there are k threads, thread i inserts
	//      (i, i), (i+k, i), (i+k*2)
	for (key = tid ; key < NUM_KEYS; key += num_threads) {
		insert(keys[key], tid);
	}

	pthread_exit(NULL);
}

void* get_phase(void *arg) {
	long tid = (long) arg;
	int key = 0;
	long lost = 0;

	for (key = tid ; key < NUM_KEYS; key += num_threads) {
		if (retrieve(keys[key]) == NULL) {
			lost++;
		}
	}
	printf("[thread %ld] %ld keys lost!\n", tid, lost);

	pthread_exit((void *)lost);
}

int main(int argc, char **argv) {
	// initialize spinlock
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
	pthread_spin_init(&readerLock, PTHREAD_PROCESS_PRIVATE);
	readers = 0;

	long i;
	pthread_t* threads;
	double start, end;

	if (argc != 2) {
		panic("usage: ./parallel_hashtable <num_threads>");
	}
	if ((num_threads = atoi(argv[1])) <= 0) {
		panic("must enter a valid number of threads to run");
	}

	srandom(time(NULL));
	for (i = 0; i < NUM_KEYS; i++) {
		keys[i] = random();
	}

	threads = malloc(sizeof (pthread_t) * num_threads);
	if (!threads) {
		panic("out of memory allocating thread handles");
	}

	// Insert keys in parallel
	start = now();
	for (i = 0; i < num_threads; i++) {
		pthread_create(&threads[i], NULL, put_phase, (void*) i);
	}

	// Barrier
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	end = now();

	printf("[main] Inserted %d keys in %f seconds\n", NUM_KEYS, end - start);

	// Reset the thread array
	memset(threads, 0, sizeof(pthread_t) * num_threads);

	// Retrieve keys in parallel
	start = now();
	for (i = 0; i < num_threads; i++) {
		pthread_create(&threads[i], NULL, get_phase, (void*) i);
	}

	// Collect count of lost keys
	long total_lost = 0;
	long *lost_keys = (long *) malloc(sizeof(long) * num_threads);
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], (void**) &lost_keys[i]);
		total_lost += lost_keys[i];
	}
	end = now();

	printf("[main] Retrieved %ld/%d keys in %f seconds\n", NUM_KEYS - total_lost, NUM_KEYS, end - start);

	return 0;
}
