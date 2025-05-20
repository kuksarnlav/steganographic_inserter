#include <iostream>
#include "MethodLSB.h"

int main(){
    string inputPathContainer = "E:/Test/container.bmp",
           inputPathMessage = "E:/Test/message.bmp",
           inputPathDir = "E:/Test/",
           inputInsertionSequence = "RRGGBB"; //RGBRGB //RRGGBB
    LSBType inputLSBType = Separate;
    unsigned char inputBitsCheckedContainer = 0b11111111;
    MethodLSB methodLSB;
    methodLSB.insertMessage(inputPathContainer,
                            inputPathMessage,
                            inputPathDir,
                            inputLSBType,
                            inputInsertionSequence,
                            inputBitsCheckedContainer);
    return 0;
}