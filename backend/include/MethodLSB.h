#pragma once

#include "Method.h"

class MethodLSB : public Method{
public:
    void insertMessage(const string &inputPathContainer,
                       const string &inputPathMessage,
                       const string &inputPathDir,
                       LSBType inputLSBType,
                       const string &inputInsertionSequence,
                       unsigned char inputBitsCheckedContainer);

    //void extractMessage();

    static long long getContainerCapacity(const string &inputPathContainer, unsigned char bitsChecked);
    static long long getMessageWeight(const string &inputPathMessage);

protected:
    const string nameBinaryMessageFileConsecutive = "message.txt",
                 nameBinaryMessageFileSeparateR = "messageR.txt",
                 nameBinaryMessageFileSeparateG = "messageG.txt",
                 nameBinaryMessageFileSeparateB = "messageB.txt";
    LSBType lsbType;
    string insertionSequence;
    unsigned char bitsCheckedContainer;

    void setLSBType(LSBType type);
    void setInsertionSequence(const string &sequence);
    void setBitsCheckedContainer(unsigned char availableBits);
};