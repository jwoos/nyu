# Env

## Build
```
make
```

or

```
gcc env.c -Wall -Wextra -std=c99 -ggdb -O0 -o life
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
- The program will not `fork` before `exec`ing to match functionality of `env` from GNU coreutils 8.29
Tested by running `env sh -c 'while true; do sleep 5; echo hi;done'` and then `ps -fu` to examine whether it had spawned a child process or not (it hadn't).
