# sockets-example
This program serves as an example of a simple client and server program that both send a message to each other and display it. Both programs use IPv4 (`AF_INET` on Linux) and use POSIX socket system calls (though right now, these programs run on Linux only as far as I've tested). Both programs work on port 50000.

# Usage
## Server
The server accepts no arguments. Just run the program and it'll wait for a client to connect.

## Client
The client requires one argument: the IP Address of the server to connect to. That's all that's required.

# Limitations
## Server
As this program is meant to be a demonstration for showing off the very basic socket APIs on Linux, the server has a limit of 1 connection *in general* from a client. Any other client connections won't be served.

This limitation is in `listen()`, in the second argument. To increase this, change this from 1 to your desired number.

## Client
There are no limitations in the client.

## Both Programs
Both programs only send a static message, meaning that this message will not change at runtime; the message is hard-coded into the program.

# License
Any and all files are in the public domain. No copyright shall be asserted over any files contained in this repository.

**Have fun learning!**
