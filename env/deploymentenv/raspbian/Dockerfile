FROM balenalib/raspberrypi3:latest
MAINTAINER Tamas Eros (tamas.eros1@gmail.com)

RUN apt-get update --allow-unauthenticated --fix-missing
RUN apt-get install -y wget \
                       wiringpi \
                       redis

WORKDIR /tmp/
RUN wget https://github.com/erostamas/common/releases/download/raspbian-v0.0.2/erostamas_common.deb
RUN apt install /tmp/erostamas_common.deb

WORKDIR /
