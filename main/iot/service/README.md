# Dependencies

- Google gRPC => compile with ``make`` and install it on your system so that it can be found.
- Compiling gRPC for ARM work with the following command: ``make HAS_PKG_CONFIG=false CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ RANLIB=arm-linux-gnueabihf-ranlib LD=arm-linux-gnueabihf-ld LDXX=arm-linux-gnueabihf-g++ AR=arm-linux-gnueabihf-ar PROTOBUF_CONFIG_OPTS="--host=arm-linux --with-protoc=/usr/local/bin/protoc" CXXFLAGS="-Wno-error=class-memaccess -Wno-error=ignored-qualifiers -Wno-error=stringop-truncation" CFLAGS="-Wno-error=class-memaccess -Wno-error=ignored-qualifiers -Wno-error=stringop-truncation -Wno-error=cast-function-type -Wno-error=implicit-function-declaration -Wno-error=implicit-fallthrough"
``
