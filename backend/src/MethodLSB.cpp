#include "MethodLSB.h"

#include <unordered_set>
#include <fstream>
#include <vector>
#include <thread>

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

unsigned char MethodLSB::getBitsCheckedContainer() const{
    return bitsCheckedContainer;
}

void MethodLSB::insertMessage(const string &inputPathContainer, const string &inputPathMessage, const string &inputPathDir,
                              LSBType inputLSBType,
                              const string &inputInsertionSequence, unsigned char inputBitsCheckedContainer){

    // Setup data
    setPathContainer(inputPathContainer);
    setPathMessage(inputPathMessage);
    setPathDir(inputPathDir);
    setLSBType(inputLSBType);
    setInsertionSequence(inputInsertionSequence);
    setBitsCheckedContainer(inputBitsCheckedContainer);
    setContainer();
    setMessage();

    // Checking container capacity
    int bitsCheckedContainerQuantity = 0;
    while (inputBitsCheckedContainer){
        if (inputBitsCheckedContainer & 1) bitsCheckedContainerQuantity++;
        inputBitsCheckedContainer >>= 1;
    }
    if (getQuantityRGBBitsPicture(container) / 8 * bitsCheckedContainerQuantity < getQuantityRGBBitsPicture(message)){
        cout << "Container capacity is too low!\n"
                "Container capacity:\t" << getQuantityRGBBitsPicture(container) / 8 * bitsCheckedContainerQuantity
             << "\nMessage capacity:\t" << getQuantityRGBBitsPicture(message) << "\n";
        return;
    }

    // Shared variables
    string containerSequence,
           messageSequence;
    char bitPosition;
    unsigned char tempBitsCheckedContainer;

    switch (inputLSBType){
        case Consecutive: {
            vector<char> shifts;

            char messageByte,
                 bitsReadCounter;
            int pixelCount,
                pixelCountMax = message.TellHeight() * message.TellWidth();
            fstream messageFile;

            auto writeMessageToFileConsecutive = [&](fstream &messageFile){
                int messageHeight = message.TellHeight(), messageWidth = message.TellWidth();
                for (char color : messageSequence){
                    switch (color){
                        case 'R': {
                            for (int y = 0; y < messageHeight; y++){
                                for (int x = 0; x < messageWidth; x++){
                                    RGBApixel *pPixel = message(x, y);
                                    messageFile << pPixel->Red;
                                }
                            }
                            break;
                        }
                        case 'G': {
                            for (int y = 0; y < messageHeight; y++){
                                for (int x = 0; x < messageWidth; x++){
                                    RGBApixel *pPixel = message(x, y);
                                    messageFile << pPixel->Green;
                                }
                            }
                            break;
                        }
                        case 'B': {
                            for (int y = 0; y < messageHeight; y++){
                                for (int x = 0; x < messageWidth; x++){
                                    RGBApixel *pPixel = message(x, y);
                                    messageFile << pPixel->Blue;
                                }
                            }
                            break;
                        }
                        default: return;
                    }
                }
            };
            auto writeFileIntoContainerConsecutive = [&](fstream &messageFile){
                for (char color : containerSequence){
                    pixelCount = 0;
                    switch (color){
                        case 'R': {
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    bitsReadCounter = 0;
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (char shift : shifts){
                                        if (bitsReadCounter == 0 || bitsReadCounter == 8){
                                            if (messageFile.eof()) return;
                                            messageFile.read(&messageByte, 1);
                                            bitsReadCounter = 0;
                                        }
                                        pPixel->Red &= ~(1 << shift);
                                        pPixel->Red |= messageByte & (1 << shift);
                                        bitsReadCounter++;
                                    }
                                    pixelCount++;
                                    if (pixelCount == pixelCountMax) goto exitR;
                                }
                            }
                            exitR:
                            break;
                        }
                        case 'G': {
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    bitsReadCounter = 0;
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (char shift : shifts){
                                        if (bitsReadCounter == 0 || bitsReadCounter == 8){
                                            if (messageFile.eof()) return;
                                            messageFile.read(&messageByte, 1);
                                            bitsReadCounter = 0;
                                        }
                                        pPixel->Green &= ~(1 << shift);
                                        pPixel->Green |= messageByte & (1 << shift);
                                        bitsReadCounter++;
                                    }
                                    pixelCount++;
                                    if (pixelCount == pixelCountMax) goto exitG;
                                }
                            }
                            exitG:
                            break;
                        }
                        case 'B': {
                            for (int y = 0; y < stegocontainer.TellHeight(); y++){
                                for (int x = 0; x < stegocontainer.TellWidth(); x++){
                                    bitsReadCounter = 0;
                                    RGBApixel *pPixel = stegocontainer(x, y);
                                    for (char shift : shifts){
                                        if (bitsReadCounter == 0 || bitsReadCounter == 8){
                                            if (messageFile.eof()) return;
                                            messageFile.read(&messageByte, 1);
                                            bitsReadCounter = 0;
                                        }
                                        pPixel->Blue &= ~(1 << shift);
                                        pPixel->Blue |= messageByte & (1 << shift);
                                        bitsReadCounter++;
                                    }
                                    pixelCount++;
                                    if (pixelCount == pixelCountMax) goto exitB;
                                }
                            }
                            exitB:
                            break;
                        }
                        default: return;
                    }
                }
            };

            // Creating and initializing message.bin
            messageSequence = inputInsertionSequence.substr(3, 3);
            messageFile.open(nameBinaryMessageFileConsecutive, ios::out | ios::binary);
            if (!messageFile.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileConsecutive << "!\n";
                return;
            }
            writeMessageToFileConsecutive(messageFile);
            messageFile.close();

            // Creating and initializing stegocontainer
            containerSequence = inputInsertionSequence.substr(0, 3); // Opening message file
            setStegocontainer(); //stegocontainer = container;
            messageFile.open(nameBinaryMessageFileConsecutive, ios::in | ios::binary);
            if (!messageFile.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileConsecutive << "!\n";
                return;
            }
            bitPosition = 0; // Filling vector of shifts
            tempBitsCheckedContainer = bitsCheckedContainer;
            while (tempBitsCheckedContainer){
                if (tempBitsCheckedContainer & 1) shifts.push_back(bitPosition);
                bitPosition++;
                tempBitsCheckedContainer >>= 1;
            }
            if (shifts.empty()) return;
            writeFileIntoContainerConsecutive(messageFile);
            messageFile.close();
            stegocontainer.WriteToFile(pathStegocontainer.c_str()); // Creating stegocontainer picture
            break;
        }
        case Separate: {
            vector<char> shiftsR,
                         shiftsG,
                         shiftsB;

            containerSequence += inputInsertionSequence[0];
            containerSequence += inputInsertionSequence[2];
            containerSequence += inputInsertionSequence[4];
            messageSequence += inputInsertionSequence[1];
            messageSequence += inputInsertionSequence[3];
            messageSequence += inputInsertionSequence[5];

            fstream messageFileR,
                    messageFileG,
                    messageFileB;

            /// Functions for inserting message color component into container color component
            auto writeMessageToFileSeparateR = [&](fstream &messageFileR){
                int messageHeight = message.TellHeight(), messageWidth = message.TellWidth();
                for (int y = 0; y < messageHeight; y++){
                    for (int x = 0; x < messageWidth; x++){
                        RGBApixel *pPixel = message(x, y);
                        messageFileR << pPixel->Red;
                    }
                }
            };
            auto writeMessageToFileSeparateG = [&](fstream &messageFileG){
                int messageHeight = message.TellHeight(), messageWidth = message.TellWidth();
                for (int y = 0; y < messageHeight; y++){
                    for (int x = 0; x < messageWidth; x++){
                        RGBApixel *pPixel = message(x, y);
                        messageFileG << pPixel->Green;
                    }
                }
            };
            auto writeMessageToFileSeparateB = [&](fstream &messageFileB){
                int messageHeight = message.TellHeight(), messageWidth = message.TellWidth();
                for (int y = 0; y < messageHeight; y++){
                    for (int x = 0; x < messageWidth; x++){
                        RGBApixel *pPixel = message(x, y);
                        messageFileB << pPixel->Blue;
                    }
                }
            };

            /// Functions for inserting message color components into container color components
            const int   pixelRCountMax = message.TellHeight() * message.TellWidth(),
                        pixelGCountMax = pixelRCountMax,
                        pixelBCountMax = pixelRCountMax;
            auto writeFileIntoContainerSeparateR = [&](fstream &messageFileR){
                int pixelRCount = 0;
                const int   stegocontainerHeight = stegocontainer.TellHeight(),
                            stegocontainerWidth = stegocontainer.TellWidth();
                char messageByte,
                     bitsReadCounter;
                for (int y = 0; y < stegocontainerHeight; y++){
                    for (int x = 0; x < stegocontainerWidth; x++){
                        bitsReadCounter = 0;
                        RGBApixel *pPixel = stegocontainer(x, y);
                        for (char shift : shiftsR){
                            if (bitsReadCounter == 0 || bitsReadCounter == 8){
                                if (messageFileR.eof()) return;
                                messageFileR.read(&messageByte, 1);
                                bitsReadCounter = 0;
                            }
                            pPixel->Red &= ~(1 << shift);
                            pPixel->Red |= messageByte & (1 << shift);
                            bitsReadCounter++;
                        }
                        pixelRCount++;
                        if (pixelRCount == pixelRCountMax) return;
                    }
                }
            };
            auto writeFileIntoContainerSeparateG = [&](fstream &messageFileG){
                int pixelGCount = 0,
                    stegocontainerHeight = stegocontainer.TellHeight(),
                    stegocontainerWidth = stegocontainer.TellWidth();
                char messageByte,
                     bitsReadCounter;
                for (int y = 0; y < stegocontainerHeight; y++){
                    for (int x = 0; x < stegocontainerWidth; x++){
                        bitsReadCounter = 0;
                        RGBApixel *pPixel = stegocontainer(x, y);
                        for (char shift : shiftsG){
                            if (bitsReadCounter == 0 || bitsReadCounter == 8){
                                if (messageFileG.eof()) return;
                                messageFileG.read(&messageByte, 1);
                                bitsReadCounter = 0;
                            }
                            pPixel->Green &= ~(1 << shift);
                            pPixel->Green |= messageByte & (1 << shift);
                            bitsReadCounter++;
                        }
                        pixelGCount++;
                        if (pixelGCount == pixelGCountMax) return;
                    }
                }
            };
            auto writeFileIntoContainerSeparateB = [&](fstream &messageFileB){
                int pixelBCount = 0,
                    stegocontainerHeight = stegocontainer.TellHeight(),
                    stegocontainerWidth = stegocontainer.TellWidth();
                char messageByte,
                     bitsReadCounter;
                for (int y = 0; y < stegocontainerHeight; y++){
                    for (int x = 0; x < stegocontainerWidth; x++){
                        bitsReadCounter = 0;
                        RGBApixel *pPixel = stegocontainer(x, y);
                        for (char shift : shiftsB){
                            if (bitsReadCounter == 0 || bitsReadCounter == 8){
                                if (messageFileB.eof()) return;
                                messageFileB.read(&messageByte, 1);
                                bitsReadCounter = 0;
                            }
                            pPixel->Blue &= ~(1 << shift);
                            pPixel->Blue |= messageByte & (1 << shift);
                            bitsReadCounter++;
                        }
                        pixelBCount++;
                        if (pixelBCount == pixelBCountMax) return;
                    }
                }
            };


            // Filling vector of shifts
            bitPosition = 0;
            tempBitsCheckedContainer = bitsCheckedContainer;
            while (tempBitsCheckedContainer){
                if (tempBitsCheckedContainer & 1) shiftsR.push_back(bitPosition);
                bitPosition++;
                tempBitsCheckedContainer >>= 1;
            }
            if (shiftsR.empty()) return;
            shiftsG = shiftsR;
            shiftsB = shiftsR;

            messageFileR.open(nameBinaryMessageFileSeparateR, ios::out | ios::binary);
            messageFileG.open(nameBinaryMessageFileSeparateG, ios::out | ios::binary);
            messageFileB.open(nameBinaryMessageFileSeparateB, ios::out | ios::binary);
            if (!messageFileR.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateR << "!\n";
                return;
            }
            if (!messageFileG.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateG << "!\n";
                return;
            }
            if (!messageFileB.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateB << "!\n";
                return;
            }

            /// Multithreaded file fulfilling
            writeMessageToFileSeparateR(messageFileR);
            writeMessageToFileSeparateG(messageFileG);
            writeMessageToFileSeparateB(messageFileB);

            messageFileR.close();
            messageFileG.close();
            messageFileB.close();

            setStegocontainer();


            messageFileR.open(nameBinaryMessageFileSeparateR, ios::in | ios::binary);
            messageFileG.open(nameBinaryMessageFileSeparateG, ios::in | ios::binary);
            messageFileB.open(nameBinaryMessageFileSeparateB, ios::in | ios::binary);
            if (!messageFileR.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateR << "!\n";
                return;
            }
            if (!messageFileG.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateG << "!\n";
                return;
            }
            if (!messageFileB.is_open()){
                cout << "Problem with opening " << nameBinaryMessageFileSeparateB << "!\n";
                return;
            }


            /// Multithreaded insertion
            vector<thread> threads;
            for (size_t i = 0; i < containerSequence.size(); i++){
                switch (containerSequence[i]){
                    case 'R':{
                        switch (messageSequence[i]){
                            case 'R':{
                                threads.emplace_back(writeFileIntoContainerSeparateR, ref(messageFileR));
                                break;
                            }
                            case 'G':{
                                threads.emplace_back(writeFileIntoContainerSeparateR, ref(messageFileG));
                                break;
                            }
                            case 'B': {
                                threads.emplace_back(writeFileIntoContainerSeparateR, ref(messageFileB));
                                break;
                            }
                        }
                        break;
                    }
                    case 'G':{
                        switch (messageSequence[i]){
                            case 'R':{
                                threads.emplace_back(writeFileIntoContainerSeparateG, ref(messageFileR));
                                break;
                            }
                            case 'G':{
                                threads.emplace_back(writeFileIntoContainerSeparateG, ref(messageFileG));
                                break;
                            }
                            case 'B': {
                                threads.emplace_back(writeFileIntoContainerSeparateG, ref(messageFileB));
                                break;
                            }
                        }
                        break;
                    }
                    case 'B': {
                        switch (messageSequence[i]){
                            case 'R':{
                                threads.emplace_back(writeFileIntoContainerSeparateB, ref(messageFileR));
                                break;
                            }
                            case 'G':{
                                threads.emplace_back(writeFileIntoContainerSeparateB, ref(messageFileG));
                                break;
                            }
                            case 'B': {
                                threads.emplace_back(writeFileIntoContainerSeparateB, ref(messageFileB));
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            /// Waiting threads to finish
            for (auto &t : threads){
                if (t.joinable()) t.join();
            }

            /// Closing files
            messageFileR.close();
            messageFileG.close();
            messageFileB.close();

            /// Creating stegocontainer picture
            stegocontainer.WriteToFile(pathStegocontainer.c_str());
            break;
        }
        default: return;
    }
}