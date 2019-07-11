#include "StringCommandAdapter.h"

#include <boost/algorithm/string.hpp>
#include <vector>

#include "SetColorCommand.h"
#include "SetIntensityCommand.h"

StringCommandAdapter::StringCommandAdapter(OutputControl& outputControl)
: _outputControl(outputControl) {
}

CommandPtr StringCommandAdapter::convertMessage(const char* message) const {
    LOG_DEBUG << "[StringCommandAdapter] Converting message: " << message;
    std::vector<std::string> tokens;
    boost::split(tokens,message,boost::is_any_of(" "));
    if (tokens.size() == 2 && tokens[0] == "setintensity") {
        LOG_DEBUG << "[StringCommandAdapter] setintensity command received";
        return std::unique_ptr<SetIntensityCommand>(new SetIntensityCommand(_outputControl, tokens[1]));
    } else if (tokens.size() == 4 && tokens[0] == "setcolor") {
        LOG_DEBUG << "[StringCommandAdapter] setcolor command received";
        return std::unique_ptr<SetColorCommand>(new SetColorCommand(_outputControl, tokens[1], tokens[2], tokens[3]));
    } else if (tokens.size() > 0) {
        LOG_DEBUG << "[StringCommandAdapter] unknown command received: " << tokens[0];
        return nullptr;
    }
    return nullptr;
}