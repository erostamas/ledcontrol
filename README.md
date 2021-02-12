LEDCONTROL

docker run -d -h ledcontrol --name ledcontrol --privileged --restart unless-stopped --network host -v /ledcontrol_files/:/ledcontrol_files erostamas/ledcontrol_deployment_raspbian_master

docker run -d --name ledcontrol_redis --restart unless-stopped --network host redis
