#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "erostamas/Logging.h"
#include "erostamas/Config.h"
#include "LedControl.h"

bool stopControlRequested = false;

void signalHandler(int signum) {
    LOG_INFO << "Interrupt signal received, terminating...";
    exit(0);
}

int main() {
    Config config("/ledcontrol_files/config.json");
    std::string loglevel = config.get<std::string>("loglevel", "INFO");
    std::string logDir = config.get<std::string>("logdir", "/ledcontrol_files/log/");
    std::string logFilePattern = config.get<std::string>("logdir", "led_%Y%m%d_%H%M%S.log");
    uint64_t rotationSize =  config.get<uint64_t>("rotation_size", 1 * 1024 * 1024);
    uint64_t logDirSizeLimit =  config.get<uint64_t>("log_dir_size_limit", 10 * 1024 * 1024);

    init_logging(logDir, logFilePattern, loglevel, rotationSize, logDirSizeLimit);

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    LOG_INFO << "LEDCONTROL starting up...\n";
    LedControl ledcontrol;

    ledcontrol.run();
	exit(0);
}
