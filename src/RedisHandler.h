#pragma once

#include <cpp_redis/cpp_redis>

class RedisHandler {
public:
    RedisHandler() {
        _redisClient.connect("192.168.1.247", 6379);
    }

    void store() {
        std::vector<std::pair<std::string, std::string>> values = {{"key", "value"}, {"key2", "value2"}, {"Julcsi", "Nori"}};
        _redisClient.hmset("ledcontrol_process_data", values);
        _redisClient.sync_commit();
    }

private:
    cpp_redis::client _redisClient;
};