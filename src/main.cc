#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "erostamas/Logging.h"
#include "LedControl.h"

bool stopControlRequested = false;

void signalHandler(int signum) {
    LOG_INFO << "Interrupt signal received, terminating...";
    exit(0);
}

void parseCommandlineArguments(int argc, char* argv[], std::string& loglevel) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-l") || (arg == "--loglevel")) {
            if (i + 1 < argc) {
                loglevel = argv[i + 1];
            }
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    std::string loglevel = "INFO";
    if (argc > 2) {
        parseCommandlineArguments(argc, argv, loglevel);
    }
    init_logging("/ledcontrol_files/led.log", loglevel);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    LOG_INFO << "LEDCONTROL starting up...\n";
    LedControl ledcontrol;

    ledcontrol.run();
	exit(0);
}
