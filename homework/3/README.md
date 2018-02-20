# du

## Build
```
make
```

or

```
gcc du.c -Wall -Wextra -std=c99 -ggdb -O0 -o du
gcc du_ntfw.c -Wall -Wextra -std=c99 -ggdb -O0 -o du_ntfw
```

---

Tested with the following GCC

```
$ gcc --version
gcc (GCC) 7.3.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Notes
- It does not work with single files as the original command would
	- .e.g `du dir1/file1` does not work as the current implementation stands
- It doesn't deal well with directory names passed in such as `.` and `..`
