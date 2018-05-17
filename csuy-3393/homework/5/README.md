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
- The message sent can be a bit confusing as it would be a pain to implement it so that it's the proper line without something like ncurses
- Tested on the same machine as well as on local network with two machines
- Without a specified port the server will use 8000
- The client requires a port as well if the IP is specified if neither are specified it will use localhost (127.0.0.1) and port 8000
