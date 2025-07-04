#pragma once

#include "Method.h"
#include <vector>

using namespace std;

class MethodZhaoKoch : public Method{
public:
    void insertMessage(const string &inputPathContainer,
                       const string &inputPathMessage,
                       const string &inputPathDir,
                       const string &inputMessageSequence,
                       const string &inputContainerSequence,
                       double inputThreshold,
                       int inputCoef1X,
                       int inputCoef1Y,
                       int inputCoef2X,
                       int inputCoef2Y);

    static long long getContainerCapacity(const string &inputPathContainer);
    static long long getMessageWeight(const string &inputPathContainer);

protected:
    const string nameMessageFile = "message.txt";

    string messageSequence,
           containerSequence;

    int coef1X,
        coef1Y,
        coef2X,
        coef2Y;

    double threshold;

    bool setMessageSequence(const string &inputMessageSequence);
    bool setContainerSequence(const string &inputContainerSequence);
    bool setCoefs(int inputCoef1X, int inputCoef1Y, int inputCoef2X, int inputCoef2Y);
};