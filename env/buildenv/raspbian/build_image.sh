#/bin/bash

OPERATING_SYSTEM="raspbian"

set -e

echo "Building ledcontrol build image for $OPERATING_SYSTEM as user: $USER"

echo "Environment variables:"
env

cd $(dirname $0)

ROOT_DIR=$(git rev-parse --show-toplevel)

SUCCESS=0

cd $ROOT_DIR
BRANCH_NAME=${BRANCH_NAME:-$(git rev-parse --abbrev-ref HEAD)}
IMAGE_NAME="erostamas/ledcontrol_build_${OPERATING_SYSTEM}_${BRANCH_NAME}"
echo "Image name is: $IMAGE_NAME, branch name is: $BRANCH_NAME"

cd $ROOT_DIR
docker build --build-arg DATE=$(date +%s) -t "$IMAGE_NAME" $ROOT_DIR/env/buildenv/$OPERATING_SYSTEM/
docker login --username=erostamas --password 749af946-ad0c-4d57-ade7-dfcc06efb7e4 docker.io
docker push "$IMAGE_NAME":latest

SUCCESS=$?
echo "Done building ledcontrol build image for $OPERATING_SYSTEM"

return $SUCCESS