#/bin/bash

cd $(dirname $0)

ROOT_DIR=$(git rev-parse --show-toplevel)

docker run -it --privileged --name ledcontrol_build -h ledcontrol_build -v ${ROOT_DIR}:/repo/ erostamas/ledcontrol_build_raspbian_master /bin/bash
