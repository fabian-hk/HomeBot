# Dependencies
- Google gRPC => compile with ``make`` and install it on your system so that it can be found.

# Build
- On Linux x86-64 you can build this library with ``./build/build.sh 0`` from this directory.
- On Raspbery Pi you can build this library with ``./build/build.sh 1`` from this directory.
- IotService needs the capability to create raw sockets for ping requests. 
  You can grant the permission with ```sudo setcap CAP_NET_RAW=ep ./out/IotService```.
