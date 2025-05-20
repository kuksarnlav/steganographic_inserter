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

    unsigned char getBitsCheckedContainer() const;

protected:
    const string nameBinaryMessageFileConsecutive = "message.bin",
                 nameBinaryMessageFileSeparateR = "messageR.bin",
                 nameBinaryMessageFileSeparateG = "messageG.bin",
                 nameBinaryMessageFileSeparateB = "messageB.bin";
    LSBType lsbType;
    string insertionSequence;
    unsigned char bitsCheckedContainer;

    void setLSBType(LSBType type);
    void setInsertionSequence(const string &sequence);
    void setBitsCheckedContainer(unsigned char availableBits);
};