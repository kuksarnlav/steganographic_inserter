#include "InserterBMP.h"
#include "EasyBMP.h"
#include <fstream>

void InserterBMP::setContainer(std::string containerPath){
    container.ReadFromFile(containerPath.c_str());
    this->containerPath = containerPath;
}
void InserterBMP::setMsg(std::string msgPath){
    msg.ReadFromFile(msgPath.c_str());
    this->msgPath = msgPath;
}
void InserterBMP::setStegocontainerPath(std::string directoryPath){
    stegocontainerPath = directoryPath + stegocontainerFileName;
}
void InserterBMP::setContainerNoisePath(std::string directoryPath){
    containerNoisePath = directoryPath + containerNoiseFileName;
}
void InserterBMP::setStegocontainerNoisePath(std::string directoryPath){
    stegocontainerNoisePath = directoryPath + stegocontainerNoiseFileName;
}

size_t InserterBMP::getContainerAvailableRGBBits(){
    return (size_t)container.TellHeight() * (size_t)container.TellWidth() * 3;
}
size_t InserterBMP::getMsgRGBBits(){
    return msg.TellHeight() * msg.TellWidth() * 24;
}
size_t InserterBMP::getBitsChanged(){
    return bitsChanged;
}
std::string InserterBMP::getContainerPath(){
    return containerPath;
}
std::string InserterBMP::getMsgPath(){
    return msgPath;
}
std::string InserterBMP::getContainerNoisePath(){
    return containerNoisePath;
}
std::string InserterBMP::getStegocontainerNoisePath(){
    return stegocontainerNoisePath;
}
std::string InserterBMP::getStegocontainerPath(){
    return stegocontainerPath;
}
std::string InserterBMP::getBitsChangedPercentage(){
    return (std::to_string((double)bitsChanged/(double)this->getContainerAvailableRGBBits() * 100) + "%");
}

void InserterBMP::makeStegocontainer(){
    std::fstream msgRGBFile("msgRGBFile.bin", std::ios::out | std::ios::binary);
    if (msgRGBFile.is_open()){
        int msgHeight = msg.TellHeight(), msgWidth = msg.TellWidth();
        for (int y = 0; y < msgHeight; y++){
            for (int x = 0; x < msgWidth; x++){
                RGBApixel *pPixel = msg(x, y);
                msgRGBFile << pPixel->Red;
            }
        }
        for (int y = 0; y < msgHeight; y++){
            for (int x = 0; x < msgWidth; x++){
                RGBApixel *pPixel = msg(x, y);
                msgRGBFile << pPixel->Green;
            }
        }
        for (int y = 0; y < msgHeight; y++){
            for (int x = 0; x < msgWidth; x++){
                RGBApixel *pPixel = msg(x, y);
                msgRGBFile << pPixel->Blue;
            }
        }
    } else {
        std::cerr << "Problem with opening msgRGBFile.bin for writing!\n";
    }
    msgRGBFile.close();

    bitsChanged = 0;
    BMP stegocontainer;
    stegocontainer.ReadFromFile(containerPath.c_str());
    msgRGBFile.open("msgRGBFile.bin", std::ios::in | std::ios::binary);
    if (msgRGBFile.is_open()){
        char c;
        msgRGBFile.read(&c, 1);
        int shift = 0;
        int containerHeight = stegocontainer.TellHeight(), containerWidth = stegocontainer.TellWidth();
        for (int y = 0; y < containerHeight; y++){
            for (int x = 0; x < containerWidth; x++){
                RGBApixel *pPixel = stegocontainer(x, y);
                unsigned char msgBit = c >> shift & 0b00000001;
                if (pPixel->Blue >> 7 == msgBit){
                    bitsChanged++;
                }
                pPixel->Blue |= msgBit;
                shift++;
                if (shift == 7){
                    msgRGBFile.read(&c, 1);
                    shift = 0;
                }
                if (msgRGBFile.eof()) goto readingExit;
            }
        }
        for (int y = 0; y < containerHeight; y++){
            for (int x = 0; x < containerWidth; x++){
                RGBApixel *pPixel = stegocontainer(x, y);
                unsigned char msgBit = c >> shift & 0b00000001;
                if (pPixel->Red >> 7 == msgBit){
                    bitsChanged++;
                }
                pPixel->Red |= msgBit;
                shift++;
                if (shift == 7){
                    msgRGBFile.read(&c, 1);
                    shift = 0;
                }
                if (msgRGBFile.eof()) goto readingExit;
            }
        }
        for (int y = 0; y < containerHeight; y++){
            for (int x = 0; x < containerWidth; x++){
                RGBApixel *pPixel = stegocontainer(x, y);
                unsigned char msgBit = c >> shift & 0b00000001;
                if (pPixel->Red >> 7 == msgBit){
                    bitsChanged++;
                }
                pPixel->Green |= msgBit;
                shift++;
                if (shift == 7){
                    msgRGBFile.read(&c, 1);
                    shift = 0;
                }
                if (msgRGBFile.eof()) goto readingExit;
            }
        }
        msgRGBFile.close();
    } else {
        std::cerr << "Problem with opening msgRGBFile.bin for reading!\n";
    }
    readingExit:
    stegocontainer.WriteToFile(stegocontainerPath.c_str());
}
void InserterBMP::makeContainerNoisePic(){
    BMP containerNoise;
    containerNoise.ReadFromFile(containerPath.c_str());
    int containerHeight = containerNoise.TellHeight(), containerWidth = containerNoise.TellWidth();
    for (int y = 0; y < containerHeight; y++){
        for (int x = 0; x < containerWidth; x++){
            RGBApixel *pPixel = containerNoise(x, y);

            pPixel->Red &= 0b00000001;
            pPixel->Green &= 0b00000001;
            pPixel->Blue &= 0b00000001;

            pPixel->Red <<= 7;
            pPixel->Green <<= 7;
            pPixel->Blue <<= 7;

            if (pPixel->Red) pPixel->Red |= 0b11111111;
            if (pPixel->Green) pPixel->Green |= 0b11111111;
            if (pPixel->Blue) pPixel->Blue |= 0b11111111;
        }
    }
    containerNoise.WriteToFile(containerNoisePath.c_str());
}
void InserterBMP::makeStegocontainerNoisePic(){
    BMP stegocontainerNoise;
    stegocontainerNoise.ReadFromFile(stegocontainerPath.c_str());
    int stegocontainerHeight = stegocontainerNoise.TellHeight(), stegocontainerWidth = stegocontainerNoise.TellWidth();
    for (int y = 0; y < stegocontainerHeight; y++){
        for (int x = 0; x < stegocontainerWidth; x++){
            RGBApixel *pPixel = stegocontainerNoise(x, y);

            pPixel->Red &= 0b00000001;
            pPixel->Green &= 0b00000001;
            pPixel->Blue &= 0b00000001;

            pPixel->Red <<= 7;
            pPixel->Green <<= 7;
            pPixel->Blue <<= 7;

            if (pPixel->Red) pPixel->Red |= 0b11111111;
            if (pPixel->Green) pPixel->Green |= 0b11111111;
            if (pPixel->Blue) pPixel->Blue |= 0b11111111;
        }
    }
    stegocontainerNoise.WriteToFile(stegocontainerNoisePath.c_str());
}
