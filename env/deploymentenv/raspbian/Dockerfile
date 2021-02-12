FROM balenalib/raspberrypi3:latest
MAINTAINER Tamas Eros (tamas.eros1@gmail.com)

RUN apt-get update --allow-unauthenticated --fix-missing
RUN apt-get install -y wget \
                       wiringpi \
                       redis

WORKDIR /tmp/
RUN wget https://github.com/erostamas/common/releases/download/raspbian-v0.0.3/erostamas_common.deb
RUN apt install /tmp/erostamas_common.deb

RUN wget https://github.com/erostamas/ledcontrol/releases/download/raspbian-v0.0.1/ledcontrol.deb
RUN apt install /tmp/ledcontrol.deb

WORKDIR /

ENTRYPOINT /usr/bin/ledcontrol
