#pragma once

#include "EasyBMP.h"

using namespace std;

class Statistics{
public:

    Statistics();

    string getContainerBit1Percentage() const;
    string getMessageBit1Percentage() const;
    string getStegocontainerBit1Percentage() const;
    string getStegocontainerChangedBitsPercentage() const;

    void calculateStatistics(const string &containerPath, const string &messagePath, const string &stegocontainerPath);

protected:
    BMP container;
    BMP message;
    BMP stegocontainer;

    float containerBit1Percentage;
    float messageBit1Percentage;
    float stegocontainerBit1Percentage;
    float stegocontainerChangedBitsPercentage;

    static unsigned char table1BitCount[256];
    static void initBite1Bits();
};