#include "StringCommandAdapter.h"

#include <boost/algorithm/string.hpp>
#include <vector>

#include "SetColorCommand.h"

StringCommandAdapter::StringCommandAdapter(OutputControl& outputControl)
: _outputControl(outputControl) {
}

CommandPtr StringCommandAdapter::convertMessage(const char* message) const {
    
    //std::vector<std::string> split_message = Utils::split(message, sep);
    //if (split_message[0] == "setcolor") {
    //    setColor(split_message[1], split_message[2], split_message[3]);
    //} else if (split_message[0] == "setred") {
    //    setRed(split_message[1]);
    //} else if (split_message[0] == "setgreen") {
    //    setGreen(split_message[1]);
    //} else if (split_message[0] == "setblue") {
    //    setBlue(split_message[1]);
    //} else if (split_message[0] == "setintensity") {
    //    setIntensity(split_message[1]);
    //} else if (split_message[0] == "setloglevel") {
    //    // TODO
    //    //set_loglevel(split_message[1]);
    //}
    LOG_DEBUG << "[StringCommandAdapter] Converting message: " << message << std::endl;
    std::vector<std::string> tokens;
    boost::split(tokens,message,boost::is_any_of(" "));
    if (tokens.size() != 4 || tokens[0] != "setcolor") {
        return nullptr;
    } else {
        LOG_DEBUG << "[StringCommandAdapter] setcolor command received" << std::endl;
        return std::unique_ptr<SetColorCommand>(new SetColorCommand(_outputControl, tokens[1], tokens[2], tokens[3]));
    }
    return nullptr;
}