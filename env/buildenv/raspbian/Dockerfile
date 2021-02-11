ARG DATE=default

FROM balenalib/raspberrypi3:latest
MAINTAINER Tamas Eros (tamas.eros1@gmail.com)

RUN apt-get update --allow-unauthenticated --fix-missing
RUN apt-get install -y build-essential \
                       git \
                       cmake \
                       wget \
                       wiringpi \
                       libgmock-dev

WORKDIR /tmp/
RUN git clone https://github.com/Cylix/cpp_redis.git
WORKDIR /tmp/cpp_redis
RUN git submodule init && git submodule update
RUN mkdir build
WORKDIR /tmp/cpp_redis/build
RUN cmake .. -DCMAKE_BUILD_TYPE=Release && make && make install

WORKDIR /tmp/
RUN echo "$DATE"
RUN wget https://github.com/erostamas/common/releases/download/raspbian-v0.0.3/erostamas_common.deb
RUN apt install /tmp/erostamas_common.deb

WORKDIR /
