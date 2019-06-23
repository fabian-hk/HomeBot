# Dependencies

- Google gRPC => compile with ``make`` and install it on your system so that it can be found.

# Install
- IotService need the capability to create raw sockets for ping requests. 
  You can grant the permission with ```sudo setcap CAP_NET_RAW=ep ./out/IotService```.
