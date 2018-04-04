# Chat

## Build
```
make
```

---

```
$ gcc --version
gcc (GCC) 7.3.1 20180312
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Notes
- Exit the application with `Ctrl-C` (`SIGTERM`) for both server and client
- Run the application with no arguments to see the usage
- Only takes IP and not hostnames for client
- There is a period of time after the application is killed that the port is unavailable which seems to be to flush out any requests still pending on that port
- The message can be a bit confusing as I don't know how to keep the "input" at the bottom of the screen without ncurses
