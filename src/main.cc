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

TcpInterface tcpint;
UnixDomainSocketInterface unixint;

void startTCPListening() {
	tcpint.run();
}

void startUnixDomainListening() {
	unixint.run();
}

void signalHandler( int signum ) {
    LOG_INFO << "Interrupt signal received, terminating...\n";
    unlink("/ledcontrol_files/ledcontrol_socket_file");
    exit(0);
}

int main(void) {
    init_logging();
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    LedControl ledcontrol(&tcpint, &unixint);

	std::thread t1(startTCPListening);
    std::thread t2(startUnixDomainListening);
    ledcontrol.run();
	exit(0);
}
