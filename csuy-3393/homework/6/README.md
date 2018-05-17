# Chat

## Build
```
make
```

---

```
$ gcc --version
gcc (GCC) 7.3.1 20180406
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Notes
- Run the application with no arguments to see the usage
- Tested on the same machine as well as on local network with two machines
- Run server with `./chat server`, which will listen on port 8000
- Run client with `./chat client <name>`, which will attempt to connect to 127.0.0.1:8000 by default with name `<name>`

### Server
- Exit the application with `Ctrl-C` (`SIGTERM`)
- There is a period of time after the application is killed that the port is unavailable which seems to be to flush out any requests still pending on that port
- Without a specified port the server will use 8000

### Client
- Exit the application by sending `/quit` or `Ctrl-C` (`SIGTERM`)
- Takes name as a required first argument
- Only takes IP and not hostnames
- The message sent can be a bit confusing as it would be a pain to implement it so that it's the proper line without something like ncurses
- The client requires a port as well if the IP is specified if neither are specified it will use localhost (127.0.0.1) and port 8000

## Changes
### Server
- Select is not needed anymore as each connection is on its own thread

### Client
- Gave special meaning to `/quit` when sent as a message
- Gave special meaning to `/name`, which sets the name
- Client takes in name as part of command line arguments
- Changed printing out messages
  - Previously it took the server's IP and port and showed it as part of message
  - Now it just shows the message as the IP and port are embedded in the message
