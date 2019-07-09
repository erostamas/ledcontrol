#include "erostamas/ICommand.h"

#include "erostamas/Logging.h"

class SetColorCommand : public ICommand {
public:
    SetColorCommand(OutputControl& outputControl, const std::string& red, const std::string& green, const std::string& blue)
    : _outputControl(outputControl)
    , _red(red)
    , _green(green)
    , _blue(blue) {LOG_DEBUG << "SETCOLOR" << std::endl;}

    virtual void execute() override {
        LOG_DEBUG << "Executing setcolor command with parameters: " << _red << " " << _green << " " << _blue << std::endl;
        _outputControl.setColor(_red, _green, _blue);
    }

private:
    OutputControl& _outputControl;
    const std::string _red;
    const std::string _green;
    const std::string _blue;
};