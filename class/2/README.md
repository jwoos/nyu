# Lecture 2

### >> operator
1. skip leading whitespace
2. read in "valid" chars
3. stop at trailing whitespace or "invalid" chars
4. stire valid results in given variable

### Pointers
1. Derefef `nullptr`
2. Memory leak (garbage on heap)
3. Double delete

### Operator overloading
- `b2 = b1 + 100`
	- operator has to be overloaded
	- constructor is not marked explicit
- `b2 = 100 + b1`
	- requires all of the above and for the operator to be a nonmember
