#include "MethodLSB.h"

#include <unordered_set>
#include <fstream>
#include <vector>
#include <thread>
#include <bitset>
#include <filesystem>
#include <algorithm>

void MethodLSB::setLSBType(LSBType type){
    lsbType = type;
}

void MethodLSB::setInsertionSequence(const string &sequence){
    if (sequence.size() != 6) return;

    // picture channel sequence must be permutation of 'R','G','B'
    auto isTripletUnique = [](char c1, char c2, char c3) -> bool{
        unordered_set<char> set;
        set.insert(c1);
        set.insert(c2);
        set.insert(c3);
        if (set.count('R') != 1 ||
            set.count('G') != 1 ||
            set.count('B') != 1) return false;
        return true;
    };
    if (lsbType == Consecutive){
        if (!isTripletUnique(sequence[0], sequence[1], sequence[2]) ||
            !isTripletUnique(sequence[3], sequence[4], sequence[5])){
            cout << "Wrong insertion sequence: " << sequence << "!\n";
            return;
        }
    } else if (lsbType == Separate){
        if (!isTripletUnique(sequence[0], sequence[2], sequence[4]) ||
            !isTripletUnique(sequence[1], sequence[3], sequence[5])){
            cout << "Wrong insertion sequence: " << sequence << "!\n";
            return;
        }
    }
    insertionSequence = sequence;
}

void MethodLSB::setBitsCheckedContainer(unsigned char availableBits){
    bitsCheckedContainer = availableBits;
}

void MethodLSB::insertMessage(const string &inputPathContainer, const string &inputPathMessage, const string &inputPathDir,
                              LSBType inputLSBType,
                              const string &inputInsertionSequence, unsigned char inputBitsCheckedContainer){

    /// Setup inputs
    setPathContainer(inputPathContainer);
    setContainer(); /// Setup container
    setPathMessage(inputPathMessage);
    setMessage(); /// Setup message
    setPathDir(inputPathDir);
    setLSBType(inputLSBType);
    setInsertionSequence(inputInsertionSequence);
    setBitsCheckedContainer(inputBitsCheckedContainer);

    /// Exit if message can't be fully inserted
    /// Available bit planes validness
    int bitsCheckedContainerQuantity = 0;
    while (inputBitsCheckedContainer) {
        if (inputBitsCheckedContainer & 1) bitsCheckedContainerQuantity++;
        inputBitsCheckedContainer >>= 1;
    }
    if (getQuantityRGBBitsPicture(container) * bitsCheckedContainerQuantity / 8 < getQuantityRGBBitsPicture(message)){
        cout << "Container capacity is too low!\n"
                "Container capacity:\t" << getQuantityRGBBitsPicture(container) / 8 * bitsCheckedContainerQuantity
             << "\nMessage capacity:\t" << getQuantityRGBBitsPicture(message) << "\n";
        return;
    }

    /// Byte into string translation table
    string tableByteIntoStr[256];
    for (unsigned short num = 0; num < 256; num++){
        tableByteIntoStr[num] = bitset<8>(num).to_string();
    }

    /// Shared variables
    string containerSequence,
           messageSequence;
    char bitPosition;
    unsigned char tempBitsCheckedContainer;

    switch (inputLSBType){
        case Consecutive: {
            fstream messageFile;

            containerSequence = inputInsertionSequence.substr(0, 3);
            messageSequence = inputInsertionSequence.substr(3, 3);

            /// Filling vector of shifts
            vector<char> shifts;
            bitPosition = 0;
            tempBitsCheckedContainer = bitsCheckedContainer;
            while (tempBitsCheckedContainer){
                if (tempBitsCheckedContainer & 1) shifts.push_back(bitPosition);
                bitPosition++;
                tempBitsCheckedContainer >>= 1;
            }
            reverse(shifts.begin(), shifts.end());
            if (shifts.empty()) return;

            auto writeMessageToFileConsecutive = [&](fstream &messageFile){
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
            auto writeFileIntoContainerConsecutive = [&](fstream &messageFile){
                char messageByte;
                for (char color : containerSequence) {
                    switch (color) {
                        case 'R': {
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (char shift : shifts) {
                                        if (messageFile.eof()) return;
                                        messageFile.read(&messageByte, 1);
                                        pPixel->Red &= ~(1 << shift);
                                        pPixel->Red |= ((messageByte - '0') << shift);
                                    }
                                }
                            }
                            break;
                        }
                        case 'G': {
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (char shift : shifts) {
                                        if (messageFile.eof()) return;
                                        messageFile.read(&messageByte, 1);
                                        pPixel->Green &= ~(1 << shift);
                                        pPixel->Green |= ((messageByte - '0') << shift);
                                    }
                                }
                            }
                            break;
                        }
                        case 'B': {
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (char shift : shifts) {
                                        if (messageFile.eof()) return;
                                        messageFile.read(&messageByte, 1);
                                        pPixel->Blue &= ~(1 << shift);
                                        pPixel->Blue |= ((messageByte - '0') << shift);
                                    }
                                }
                            }
                            break;
                        }
                        default: return;
                    }
                }
            };

            /// Creating and initializing message.txt
            messageFile.open(nameBinaryMessageFileConsecutive, ios::in | ios::out | ios::app);
            if (!messageFile.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileConsecutive << "!\n";
                return;
            }
            /// Filling file with message
            writeMessageToFileConsecutive(messageFile);

            messageFile.clear();
            messageFile.seekg(0, ios::beg);

            /// Creating and initializing stegocontainer
            setStegocontainer();

            /// Writing message into container
            writeFileIntoContainerConsecutive(messageFile);

            messageFile.close();

            /// Creating stegocontainer picture
            stegocontainer.WriteToFile(pathStegocontainer.c_str());

            /// Deleting secondary file
            filesystem::path filepath = nameBinaryMessageFileConsecutive;
            if (filesystem::exists(filepath)) filesystem::remove(filepath);

            break;
        }
        case Separate: {
            vector<char> shifts;

            containerSequence += inputInsertionSequence[0];
            containerSequence += inputInsertionSequence[2];
            containerSequence += inputInsertionSequence[4];
            messageSequence += inputInsertionSequence[1];
            messageSequence += inputInsertionSequence[3];
            messageSequence += inputInsertionSequence[5];

            fstream messageFile;

            // Filling vector of shifts
            bitPosition = 0;
            tempBitsCheckedContainer = bitsCheckedContainer;
            while (tempBitsCheckedContainer){
                if (tempBitsCheckedContainer & 1) shifts.push_back(bitPosition);
                bitPosition++;
                tempBitsCheckedContainer >>= 1;
            }
            if (shifts.empty()) return;
            reverse(shifts.begin(), shifts.end());

            auto writeMessageToFile = [&](){
                for (const char color : messageSequence){
                    switch (color){
                        case 'R': {
                            for (int y = 0; y < message.TellHeight(); y++){
                                for (int x = 0; x < message.TellWidth(); x++){
                                    const RGBApixel *pPixel = message(x, y);
                                    messageFile << tableByteIntoStr[pPixel->Red];
                                }
                            }
                            break;
                        }
                        case 'G': {
                            for (int y = 0; y < message.TellHeight(); y++){
                                for (int x = 0; x < message.TellWidth(); x++){
                                    const RGBApixel *pPixel = message(x, y);
                                    messageFile << tableByteIntoStr[pPixel->Green];
                                }
                            }
                            break;
                        }
                        case 'B': {
                            for (int y = 0; y < message.TellHeight(); y++){
                                for (int x = 0; x < message.TellWidth(); x++){
                                    const RGBApixel *pPixel = message(x, y);
                                    messageFile << tableByteIntoStr[pPixel->Blue];
                                }
                            }
                            break;
                        }
                        default: return;
                    }
                }
            };
            auto writeMessageIntoContainer = [&](){
                char messageByte;
                const int colorChannelPixels = message.TellWidth() * message.TellHeight();
                int countPixels = 0;
                for (const char colorContainer : containerSequence){
                    switch (colorContainer){
                        case 'R':{
                            countPixels = 0;
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    if (countPixels == colorChannelPixels) goto exitR;
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (const char shift : shifts){
                                        if (messageFile.eof()) return;
                                        messageFile.read(&messageByte, 1);
                                        pPixel->Red &= ~(1 << shift);
                                        pPixel->Red |= ((messageByte - '0') << shift);
                                    }
                                    countPixels++;
                                }
                            }
                            exitR:
                            break;
                        }
                        case 'G':{
                            countPixels = 0;
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    if (countPixels == colorChannelPixels) goto exitG;
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (const char shift : shifts){
                                        if (messageFile.eof()) return;
                                        messageFile.read(&messageByte, 1);
                                        pPixel->Green &= ~(1 << shift);
                                        pPixel->Green |= ((messageByte - '0') << shift);
                                    }
                                    countPixels++;
                                }
                            }
                            exitG:
                            break;
                        }
                        case 'B':{
                            countPixels = 0;
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    if (countPixels == colorChannelPixels) goto exitB;
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (const char shift : shifts){
                                        if (messageFile.eof()) return;
                                        messageFile.read(&messageByte, 1);
                                        pPixel->Blue &= ~(1 << shift);
                                        pPixel->Blue |= ((messageByte - '0') << shift);
                                    }
                                    countPixels++;
                                }
                            }
                            exitB:
                            break;
                        }
                        default: break;
                    }
                }
            };

            messageFile.open("messageFile.txt", ios::out);
            if (!messageFile.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateR << "!\n";
                return;
            }

            /// File fulfilling
            writeMessageToFile();

            messageFile.close();

            setStegocontainer();

            messageFile.clear();
            messageFile.seekg(0, ios::beg);

            messageFile.open("messageFile.txt", ios::in);

            if (!messageFile.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateR << "!\n";
                return;
            }

            writeMessageIntoContainer();

            /// Closing files
            messageFile.close();

            filesystem::remove("messageFile.txt");

            /// Creating stegocontainer picture
            stegocontainer.WriteToFile(pathStegocontainer.c_str());
            break;
        }
        default: return;
    }
}

long long MethodLSB::getContainerCapacity(const string &inputPathContainer, unsigned char bitsChecked){
    if (bitsChecked == 0) return 0;
    BMP img;
    img.ReadFromFile(inputPathContainer.c_str());
    long long bitsCheckedCount = 0;
    while (bitsChecked){
        if (bitsChecked & 1) bitsCheckedCount++;
        bitsChecked >>= 1;
    }
	return (long long)img.TellHeight() * (long long)img.TellWidth() * 3 * bitsCheckedCount / 8;
}

long long MethodLSB::getMessageWeight(const string &inputPathMessage){
    BMP img;
    img.ReadFromFile(inputPathMessage.c_str());
    return (long long)img.TellHeight() * (long long)img.TellWidth() * 3;
}
