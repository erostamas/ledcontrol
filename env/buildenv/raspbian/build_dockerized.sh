#!/bin/bash

cd $(dirname $0)

ROOT_DIR=$(git rev-parse --show-toplevel)
BRANCH_NAME=${BRANCH_NAME:-$(git rev-parse --abbrev-ref HEAD)}
IMAGE_NAME="erostamas/common_build_raspbian_$BRANCH_NAME"

echo "Building in image: $IMAGE_NAME"


CMD="/workspace/common/env/buildenv/raspbian/build.sh && chown -R $(id -u):$(id -g) /workspace/common/build/"


echo "Executing in docker container: $CMD"
docker pull "$IMAGE_NAME"
docker run -v $ROOT_DIR:/workspace/common "$IMAGE_NAME" /bin/bash -c "$CMD"
success=$?

if [[ $success == 0 ]]; then
    echo "Execution OK"
else
    echo "Execution failed"
fi

exit ${success}
