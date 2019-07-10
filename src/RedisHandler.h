#pragma once

#include <cpp_redis/cpp_redis>

class RedisHandler {
public:
    RedisHandler() {
        _redisClient.connect("192.168.1.247", 6379);
    }

    void updateColor(unsigned red, unsigned green, unsigned blue) {
        std::vector<std::pair<std::string, std::string>> values = {{"red", std::to_string(red)}, {"green", std::to_string(green)}, {"blue", std::to_string(blue)}};
        _redisClient.hmset("ledcontrol_process_data", values);
        _redisClient.sync_commit();
    }

private:
    cpp_redis::client _redisClient;
};