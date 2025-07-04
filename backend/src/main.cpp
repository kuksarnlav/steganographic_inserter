#include <iostream>
#include "MethodLSB.h"
#include "MethodKutter.h"
#include "MethodZhaoKoch.h"
#include "Viewer.h"
#include "Statistics.h"

int main(){
         /// Consecutive LSB test
    // string inputPathContainer = "E:/Test/container.bmp",
    //        inputPathMessage = "E:/Test/message.bmp",
    //        inputPathDir = "E:/Test/",
    //        inputInsertionSequence = "RGBRGB"; //RGBRGB
    // LSBType inputLSBType = Consecutive;
    // unsigned char inputBitsCheckedContainer = 0b11111111; //0b11111111
    // MethodLSB methodLSB;
    // methodLSB.insertMessage(inputPathContainer,
    //                         inputPathMessage,
    //                         inputPathDir,
    //                         inputLSBType,
    //                         inputInsertionSequence,
    //                         inputBitsCheckedContainer);


        /// Separate LSB test
    // string inputPathContainer = "E:/container.bmp",
    //        inputPathMessage = "E:/message.bmp",
    //        inputPathDir = "E:/",
    //        inputInsertionSequence = "RRGGBB"; //RGBRGB //RRGGBB
    // LSBType inputLSBType = Separate;
    // unsigned char inputBitsCheckedContainer = 0b11111110; //0b11111111
    // MethodLSB methodLSB;
    // methodLSB.insertMessage(inputPathContainer,
    //                         inputPathMessage,
    //                         inputPathDir,
    //                         inputLSBType,
    //                         inputInsertionSequence,
    //                         inputBitsCheckedContainer);


        /// Kutter test
    // string inputPathContainer = "E:/Test/container.bmp",
    //        inputPathMessage = "E:/Test/message.bmp",
    //        inputPathDir = "E:/Test/",
    //        inputMessageSequence = "RGB",
    //        inputContainerSequence = "RGB";
    // double input_insertion_power = 1;
    // MethodKutter methodKutter;
    // methodKutter.insertMessage(inputPathContainer,
    //                            inputPathMessage,
    //                            inputPathDir,
    //                            input_insertion_power,
    //                            inputMessageSequence,
    //                            inputContainerSequence);


        /// Zhao-Koch test
    // string inputPathContainer = "E:/Test/container.bmp",
    //        inputPathMessage = "E:/Test/message.bmp",
    //        inputPathDir = "E:/Test/",
    //         inputMessageSequence = "RGB",
    //        inputContainerSequence = "RGB";
    // MethodZhaoKoch methodZhaoKoch;
    // int inputCoef1X = 1,
    //     inputCoef1Y = 2,
    //     inputCoef2X = 1,
    //     inputCoef2Y = 1;
    // double inputThreshold = 10.0;
    // methodZhaoKoch.insertMessage(inputPathContainer,
    //                              inputPathMessage,
    //                              inputPathDir,
    //                              inputMessageSequence,
    //                              inputContainerSequence,
    //                              inputThreshold,
    //                              inputCoef1X,
    //                              inputCoef1Y,
    //                              inputCoef2X,
    //                              inputCoef2Y);


        /// Viewer test
    // Viewer viewer;
    // string pathExport = "E:/Test/"; /// export path
    // string pathToImage = "E:/Test/container.bmp"; /// image for viewing path
    // vector<int> viewBits{7,6,5,4,3,2,1,0}; /// checked bit planes //7,6,5,4,3,2,1,0
    // string inputViewChannels = "G";
    // viewer.createView(viewBits, pathToImage, pathExport, inputViewChannels);


        /// Statistics test
    // Statistics statistics;
    // statistics.calculateStatistics("E:/Test/container.bmp", "E:/Test/message.bmp", "E:/Test/stegocontainer.bmp");
    // cout << statistics.getContainerBit1Percentage() << "\n"
    //     << statistics.getMessageBit1Percentage() << "\n"
    //     << statistics.getStegocontainerBit1Percentage() << "\n"
    //     << statistics.getStegocontainerChangedBitsPercentage() << "\n";
}