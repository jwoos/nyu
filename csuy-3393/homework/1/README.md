# Homework 1

## Build
```
make
```

or

```
gcc life.c -Wall -Wextra -std=c99 -ggdb -O0 -o life
```

---

Tested with the following GCC

```
$ gcc --version
gcc (GCC) 7.2.1 20180116
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Notes
- Command line arguments will take precedence over file.
```
life 1 1 life.txt 10
```
will wield a board of 1x1 no matter how big or small life.txt is

- all memory was freed
```
$ make memcheck
==23998== 
==23998== HEAP SUMMARY:
==23998==     in use at exit: 0 bytes in 0 blocks
==23998==   total heap usage: 161 allocs, 161 frees, 13,784 bytes allocated
==23998== 
==23998== All heap blocks were freed -- no leaks are possible
==23998== 
==23998== For counts of detected and suppressed errors, rerun with: -v
==23998== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
