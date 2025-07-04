#pragma once

#include <string>
#include "Method.h"

using namespace std;

class MethodKutter : public Method{
public:
    void insertMessage(const string &inputPathContainer,
                       const string &inputPathMessage,
                       const string &inputPathDir,
                       double insertion_power_value,
                       const string &inputMessageSequence,
                       const string &inputContainerSequence);

    static long long getContainerCapacity(const string &inputPathContainer);
    static long long getMessageWeight(const string &inputPathContainer);

protected:
    const string nameMessageFile = "message.txt";

    double insertion_power;

    string containerSequence;
    string messageSequence;

    void setInsertionPower(double insertion_power_value);
    bool setContainerSequence(const string &inputContainerSequence);
    bool setMessageSequence(const string &inputMessageSequence);
};