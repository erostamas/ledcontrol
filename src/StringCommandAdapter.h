#include "erostamas/ICommandAdapter.h"

#include "OutputControl.h"

class StringCommandAdapter : public ICommandAdapter {
public:
    StringCommandAdapter(OutputControl& outputControl);

    virtual CommandPtr convertMessage(const char* message) const override;

private:
    OutputControl& _outputControl;
};