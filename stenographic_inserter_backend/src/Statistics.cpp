#include "Statistics.h"

unsigned char Statistics::table1BitCount[256];

void Statistics::initBite1Bits(){
    for (unsigned int i = 0; i < 256; i++){
        table1BitCount[static_cast<unsigned char>(i)] = __builtin_popcount(i);
    }
}

Statistics::Statistics(){
    initBite1Bits();
}

string Statistics::getContainerBit1Percentage() const{
    return to_string(containerBit1Percentage).substr(0, 5) + " %";
}

string Statistics::getMessageBit1Percentage() const{
    return to_string(messageBit1Percentage).substr(0, 5) + " %";
}

string Statistics::getStegocontainerBit1Percentage() const{
    return to_string(stegocontainerBit1Percentage).substr(0, 5) + " %";
}

string Statistics::getStegocontainerChangedBitsPercentage() const{
    return to_string(stegocontainerChangedBitsPercentage).substr(0, 5) + " %";
}

void Statistics::calculateStatistics(const string &pathContainer, const string &pathMessage, const string &pathStegocontainer){
    container.ReadFromFile(pathContainer.c_str());
    message.ReadFromFile(pathMessage.c_str());
    stegocontainer.ReadFromFile(pathStegocontainer.c_str());

    long long container1BitCount = 0;
    long long message1BitCount = 0;
    long long stegocontainer1BitCount = 0;
    for (int y = 0; y < container.TellHeight(); y++){
        for (int x = 0; x < container.TellWidth(); x++){
            container1BitCount += table1BitCount[container(x, y)->Red];
            container1BitCount += table1BitCount[container(x, y)->Green];
            container1BitCount += table1BitCount[container(x, y)->Blue];
        }
    }
    for (int y = 0; y < message.TellHeight(); y++){
        for (int x = 0; x < message.TellWidth(); x++){
            message1BitCount += table1BitCount[message(x, y)->Red];
            message1BitCount += table1BitCount[message(x, y)->Green];
            message1BitCount += table1BitCount[message(x, y)->Blue];
        }
    }
    for (int y = 0; y < stegocontainer.TellHeight(); y++){
        for (int x = 0; x < stegocontainer.TellWidth(); x++){
            stegocontainer1BitCount += table1BitCount[stegocontainer(x, y)->Red];
            stegocontainer1BitCount += table1BitCount[stegocontainer(x, y)->Green];
            stegocontainer1BitCount += table1BitCount[stegocontainer(x, y)->Blue];
        }
    }
    containerBit1Percentage = (float)container1BitCount / (float)(container.TellWidth() * container.TellHeight() * 8 * 3) * 100;
    messageBit1Percentage = (float)message1BitCount / (float)(message.TellWidth() * message.TellHeight() * 8 * 3) * 100;
    stegocontainerBit1Percentage = (float)stegocontainer1BitCount / (float)(stegocontainer.TellWidth() * stegocontainer.TellHeight() * 8 * 3) * 100;

    long long stegocontainerChangedBits = 0;
    for (int y = 0; y < container.TellHeight(); y++){
        for (int x = 0; x < container.TellWidth(); x++){
            stegocontainerChangedBits += table1BitCount[container(x, y)->Red ^ stegocontainer(x, y)->Red];
            stegocontainerChangedBits += table1BitCount[container(x, y)->Green ^ stegocontainer(x, y)->Green];
            stegocontainerChangedBits += table1BitCount[container(x, y)->Blue ^ stegocontainer(x, y)->Blue];
        }
    }
    stegocontainerChangedBitsPercentage = (float)stegocontainerChangedBits / (float)(stegocontainer.TellWidth() * stegocontainer.TellHeight() * 8 * 3) * 100;
}