# Lecture 22

Hash Table

array  
base address of element = base address of array + (index * size of one element)

```c++
// a really simple hash function
int hash(int n) {
	return n % 10;
}

int anotherHash(int n, int size) {
	return n % size;
}
```

hash function: an input will always produce the same, randomized output

hash collision: when two different inputs produce the same output

### How to deal with collisions
1. primary indexing: h(n), h(n) + 1, h(n) + 2, ...
	- worst case: devolves into a linear search
	- results in primary clustering - large gaps and large groups
2. secondary indexing: h(n), h(n) + 1^2, h(n) + 2^2, h(n) + 3^2, ...
	- results in secondary clustering
3. separate chain hashing: using an array/linked list/bst/vector for the element
	- worst case: devolves into a linear search

### Hash functions

all are one way algorithms

1. `md4`: easy to implement but lacks quality
2. `md5`: ok, but rainbow tables
3. `sha-1`: ok, but has collisions
4. `sha-256`: cryptographically secure in 2016
