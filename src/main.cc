#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "Common.h"
#include "Logging.h"
#include "LedControl.h"
#include "TcpInterface.h"
#include "UnixDomainSocketInterface.h"

bool stopControlRequested = false;

UdpInterface udpint;
//UnixDomainSocketInterface unixint;

void startUDPListening() {
	udpint.run();
}

void startUnixDomainListening() {
	//unixint.run();
}

void signalHandler( int signum ) {
    LOG_INFO << "Interrupt signal received, terminating...";
    unlink("/ledcontrol_files/ledcontrol_socket_file");
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
    init_logging(loglevel);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    LOG_INFO << "LEDCONTROL starting up...\n";
    LedControl ledcontrol(&udpint);

    //std::thread t1(startUnixDomainListening);
    std::thread t2(startUDPListening);
    ledcontrol.run();
	exit(0);
}
