# Build
- On Linux x86-64 you can build this library with ``./build/build.sh 0`` from this directory.
- With ``./build/build.sh 1`` from this directory you can cross compile this library for
the ARM architecture of the Raspberry Pi. You can find information about how to setup a
cross compile environment on this [website](https://amgaera.github.io/blog/2014/04/10/cross-compiling-for-raspberry-pi-on-64-bit-linux/).
    + After you have copied the executable to the Raspberry Pi you need to grant permission to
      create raw sockets with ```sudo setcap CAP_NET_RAW=ep ./out/cping```.
