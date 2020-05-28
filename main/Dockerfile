FROM debian:10.4

RUN apt update && apt install -y python3 python3-pip \
 build-essential cmake libboost-all-dev libcurl4-openssl-dev \
 libgrpc++-dev libprotobuf-dev protobuf-compiler protobuf-compiler-grpc \
 apache2 php

WORKDIR /workdir/bot

COPY main/ .
COPY main/website/ /var/www/html/
RUN rm /var/www/html/index.html

RUN pip3 install -r requirements.txt

RUN mkdir build

WORKDIR /workdir/bot/build

RUN cmake ..
RUN make -j

WORKDIR /workdir/bot

RUN chown -R 1000:1000 /workdir/bot
RUN chown -R 1000:1000 /var/www/html

RUN groupadd -g 1000 bot
RUN useradd -r -u 1000 -g 1000 bot

CMD setcap CAP_NET_RAW=ep build/cping; \
 service apache2 start; \
 su bot -c "python3 main.py"
