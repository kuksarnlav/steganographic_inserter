#include "MethodKutter.h"

#include <bitset>
#include <fstream>
#include <filesystem>

void MethodKutter::setInsertionPower(double insertion_power_value){
    insertion_power = insertion_power_value;
}
bool MethodKutter::setMessageSequence(const string &inputMessageSequence){
    /// Sequence must be 3 characters long
    if (inputMessageSequence.size() != 3){
        cout << "Message sequence size must be 3 symbols long instead of " << inputMessageSequence.size() << " !\n";
        return false;
    }
    /// Sequence must consist of characters 'R', 'G', 'B'
    for (size_t i = 0; i < 3; i++) {
        if (inputMessageSequence[i] != 'R' && inputMessageSequence[i] != 'G' && inputMessageSequence[i] != 'B') {
            cout << "Message sequence must consist only of characters 'R', 'G', 'B'! Problem character: "
                 << inputMessageSequence[i] << " !\n";
            return false;
        }
    }
    /// Sequence must consist of unique characters
    if (inputMessageSequence[0] == inputMessageSequence[1] || inputMessageSequence[0] == inputMessageSequence[2]){
        cout << "Message sequence should be a permutation of \"RGB\"! Your combination: " << inputMessageSequence << ".\n";
        return false;
    }
    messageSequence = inputMessageSequence;
    return true;
}
bool MethodKutter::setContainerSequence(const string &inputContainerSequence){
    /// Sequence must be 3 characters long
    if (inputContainerSequence.size() != 3){
        cout << "Message sequence size must be 3 symbols long instead of " << inputContainerSequence.size() << " !\n";
        return false;
    }
    /// Sequence must consist of characters 'R', 'G', 'B'
    for (size_t i = 0; i < 3; i++) {
        if (inputContainerSequence[i] != 'R' && inputContainerSequence[i] != 'G' && inputContainerSequence[i] != 'B') {
            cout << "Message sequence must consist only of characters 'R', 'G', 'B'! Problem character: "
                 << inputContainerSequence[i] << " !\n";
            return false;
        }
    }
    /// Sequence must consist of unique characters
    if (inputContainerSequence[0] == inputContainerSequence[1] || inputContainerSequence[0] == inputContainerSequence[2]){
        cout << "Message sequence should be a permutation of \"RGB\"! Your combination: " << inputContainerSequence << ".\n";
        return false;
    }
    containerSequence = inputContainerSequence;
    return true;
}
long long MethodKutter::getContainerCapacity(const string &inputPathContainer) {
    BMP img;
    img.ReadFromFile(inputPathContainer.c_str());
    int width =  (img.TellWidth() / 5) * 5;
    int height =  (img.TellHeight() / 5) * 5;
    return width * height / (5 * 5);
}
long long MethodKutter::getMessageWeight(const string &inputPathMessage){
    BMP img;
    img.ReadFromFile(inputPathMessage.c_str());
    return img.TellWidth() * img.TellHeight() * 3 * 8;
}

void MethodKutter::insertMessage(const string &inputPathContainer,
                                 const string &inputPathMessage,
                                 const string &inputPathDir,
                                 double input_insertion_power,
                                 const string &inputMessageSequence,
                                 const string &inputContainerSequence){
    /// Setup inputs
    setPathContainer(inputPathContainer);
    setContainer(); /// Setup container
    setPathMessage(inputPathMessage);
    setMessage(); /// Setup message
    setPathDir(inputPathDir);

    /// Checking sequences' validness
    if (!setMessageSequence(inputMessageSequence)) return;
    if (!setContainerSequence(inputContainerSequence)) return;


    /// Checking if the message can be fully inserted
    if (getContainerCapacity(pathContainer) < getMessageWeight(pathMessage)){
        cout << "Container capacity:\t" << getContainerCapacity(pathContainer) << " bit(s)\n";
        cout << "Message weight:\t" << getMessageWeight(pathMessage) << " bit(s)\n";
        return;
    }

    setInsertionPower(input_insertion_power);

    /// Byte into string translation table
    string tableByteIntoStr[256];
    for (unsigned short num = 0; num < 256; num++){
        tableByteIntoStr[num] = bitset<8>(num).to_string();
    }
    auto writeMessageIntoFile = [&](fstream &messageFile){
        int messageHeight = message.TellHeight(), messageWidth = message.TellWidth();
        for (char color : messageSequence){
            switch (color){
                case 'R': {
                    for (int y = 0; y < messageHeight; y++){
                        for (int x = 0; x < messageWidth; x++){
                            RGBApixel *pPixel = message(x, y);
                            messageFile << tableByteIntoStr[pPixel->Red];
                        }
                    }
                    break;
                }
                case 'G': {
                    for (int y = 0; y < messageHeight; y++){
                        for (int x = 0; x < messageWidth; x++){
                            RGBApixel *pPixel = message(x, y);
                            messageFile << tableByteIntoStr[pPixel->Green];
                        }
                    }
                    break;
                }
                case 'B': {
                    for (int y = 0; y < messageHeight; y++){
                        for (int x = 0; x < messageWidth; x++){
                            RGBApixel *pPixel = message(x, y);
                            messageFile << tableByteIntoStr[pPixel->Blue];
                        }
                    }
                    break;
                }
                default: return;
            }
        }
    };
    auto writeFileIntoContainer = [&](fstream &messageFile, const string& contSeq){
        char messageChar;
        for (char c : contSeq){
            switch (c){
                case 'R':{
                    for (int y = 2; y < stegocontainer.TellHeight(); y += 5){
                        if (y + 5 > stegocontainer.TellHeight()) continue;
                        for (int x = 2; x < stegocontainer.TellWidth(); x += 5){
                            if (x + 5 > stegocontainer.TellWidth()) continue;
                            if (messageFile.eof()) return;
                            messageFile.read(&messageChar, 1);
                            RGBApixel *pPixel = stegocontainer(x, y);
                            auto brightness = (unsigned char)(0.299 * pPixel->Red + 0.587 * pPixel->Green + 0.114 * pPixel->Blue);
                            auto delta = (unsigned char)(insertion_power * brightness);
                            if (messageChar - '0'){
                                if ((short)pPixel->Red + (short)delta > 255) pPixel->Red = 255;
                                else pPixel->Red += delta;
                            } else {
                                if ((short)pPixel->Red - (short)delta < 0) pPixel->Red = 0;
                                else pPixel->Red -= delta;
                            }
                        }
                    }
                }
                case 'G':{
                    for (int y = 2; y < stegocontainer.TellHeight(); y += 5){
                        if (y + 5 > stegocontainer.TellHeight()) continue;
                        for (int x = 2; x < stegocontainer.TellWidth(); x += 5){
                            if (x + 5 > stegocontainer.TellWidth()) continue;
                            if (messageFile.eof()) return;
                            messageFile.read(&messageChar, 1);
                            RGBApixel *pPixel = stegocontainer(x, y);
                            auto brightness = (unsigned char)(0.299 * pPixel->Red + 0.587 * pPixel->Green + 0.114 * pPixel->Blue);
                            auto delta = (unsigned char)(insertion_power * brightness);
                            if (messageChar - '0'){
                                if ((short)pPixel->Green + (short)delta > 255) pPixel->Green = 255;
                                else pPixel->Green += delta;
                            } else {
                                if ((short)pPixel->Green - (short)delta < 0) pPixel->Green = 0;
                                else pPixel->Green -= delta;
                            }
                        }
                    }
                }
                case 'B':{
                    for (int y = 2; y < stegocontainer.TellHeight(); y += 5){
                        if (y + 5 > stegocontainer.TellHeight()) continue;
                        for (int x = 2; x < stegocontainer.TellWidth(); x += 5){
                            if (x + 5 > stegocontainer.TellWidth()) continue;
                            if (messageFile.eof()) return;
                            messageFile.read(&messageChar, 1);
                            RGBApixel *pPixel = stegocontainer(x, y);
                            auto brightness = (unsigned char)(0.299 * pPixel->Red + 0.587 * pPixel->Green + 0.114 * pPixel->Blue);
                            auto delta = (unsigned char)(insertion_power * brightness);
                            if (messageChar - '0'){
                                if ((short)pPixel->Red + (short)delta > 255) pPixel->Red = 255;
                                else pPixel->Red += delta;
                            } else {
                                if ((short)pPixel->Red - (short)delta < 0) pPixel->Red = 0;
                                else pPixel->Red -= delta;
                            }
                        }
                    }
                }
                default: break;
            }
        }
    };



    /// Creating and initializing message.txt
    fstream messageFile;
    messageFile.open(nameMessageFile, std::ios::in | std::ios::out | std::ios::app);
    if (!messageFile.is_open()){
        cout << "Problem with opening " << pathMessage << "!\n";
        return;
    }
    /// Filling file with message
    writeMessageIntoFile(messageFile);

    messageFile.clear();
    messageFile.seekg(0, std::ios::beg);

    /// Creating and initializing stegocontainer
    setStegocontainer();

    /// Writing message into container
    writeFileIntoContainer(messageFile, containerSequence);

    messageFile.close();
    /// Creating stegocontainer picture
    stegocontainer.WriteToFile(pathStegocontainer.c_str());

    /// Deleting secondary file
    filesystem::path filepath = nameMessageFile;
    if (filesystem::exists(filepath)) filesystem::remove(filepath);
}