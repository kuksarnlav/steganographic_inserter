#pragma once

#include <string>

#include "EasyBMP.h"
#include "types.h"

using namespace std;

class Method{
public:
    string getPathContainer();
    string getPathMessage();
    string getPathStegocontainer();

    void setContainer();
    void setMessage();
    void setStegocontainer();

    unsigned char getBitsCheckedViewPicture() const;

    static int getQuantityRGBBitsPicture(BMP &picture);

    //void encryptMessage(CipherType cipherType);

protected:
    const string nameStegocontainer = "stegocontainer.bmp";

    string pathContainer,
           pathMessage,
           pathStegocontainer,
           pathViewPicture;

    BMP container,
        message,
        stegocontainer;

    unsigned char bitsCheckedViewPicture;

    void setPathContainer(const string &path);
    void setPathMessage(const string &path);
    void setPathDir(const string &pathDir);
    void setBitsCheckedViewPicture(unsigned char inputBitsCheckedViewPicture);
};