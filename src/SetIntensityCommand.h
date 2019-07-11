#include "erostamas/ICommand.h"

#include "erostamas/Logging.h"

class SetIntensityCommand : public ICommand {
public:
    SetIntensityCommand(OutputControl& outputControl, const std::string& intensity)
    : _outputControl(outputControl)
    , _intensity(intensity) {}

    virtual void execute() override {
        LOG_DEBUG << "Executing setintensity command with parameter: " << _intensity;
        _outputControl.setIntensity(_intensity);
    }

private:
    OutputControl& _outputControl;
    const std::string _intensity;
};