#pragma once

#include <cpp_redis/cpp_redis>

#include "erostamas/Config.h"

class RedisHandler {
public:
    RedisHandler(std::string redisIpAddress) {
        _redisClient.connect(redisIpAddress, 6379);
    }

    void updateColor(unsigned red, unsigned green, unsigned blue) {
        std::vector<std::pair<std::string, std::string>> values = {{"red", std::to_string(red)}, {"green", std::to_string(green)}, {"blue", std::to_string(blue)}};
        _redisClient.hmset("ledcontrol_process_data", values);
        _redisClient.sync_commit();
    }

private:
    cpp_redis::client _redisClient;
};
