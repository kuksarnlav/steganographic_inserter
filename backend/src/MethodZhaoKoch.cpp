#include "MethodZhaoKoch.h"

#include <bitset>
#include <fstream>
#include <filesystem>
#include <algorithm>

bool MethodZhaoKoch::setMessageSequence(const string &inputMessageSequence){
    /// Sequence must be 3 characters long
    if (inputMessageSequence.size() != 3){
        cout << "Message sequence size must be 3 symbols long instead of " << inputMessageSequence.size() << " !\n";
        return false;
    }
    /// Sequence must consist of characters 'R', 'G', 'B'
    for (size_t i = 0; i < 3; i++){
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
bool MethodZhaoKoch::setContainerSequence(const string &inputContainerSequence){
    /// Sequence must be 3 characters long
    if (inputContainerSequence.size() != 3){
        cout << "Message sequence size must be 3 symbols long instead of " << inputContainerSequence.size() << " !\n";
        return false;
    }
    /// Sequence must consist of characters 'R', 'G', 'B'
    for (size_t i = 0; i < 3; i++){
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
bool MethodZhaoKoch::setCoefs(int inputCoef1X, int inputCoef1Y, int inputCoef2X, int inputCoef2Y){
    if (inputCoef1X == inputCoef2X && inputCoef1Y == inputCoef2Y){
        cout << "Coefficients are equal!\n";
        return false;
    }
    coef1X = inputCoef1X;
    coef1Y = inputCoef1Y;
    coef2X = inputCoef2X;
    coef2Y = inputCoef2Y;
    return true;
}

long long MethodZhaoKoch::getContainerCapacity(const string &inputPathContainer){
    BMP img;
    img.ReadFromFile(inputPathContainer.c_str());
    int width =  (img.TellWidth() / 8) * 8;
    int height =  (img.TellHeight() / 8) * 8;
    return width * height / (8 * 8);
}
long long MethodZhaoKoch::getMessageWeight(const string &inputPathMessage){
    BMP img;
    img.ReadFromFile(inputPathMessage.c_str());
    return img.TellWidth() * img.TellHeight() * 3 * 8;
}

void MethodZhaoKoch::insertMessage(const string &inputPathContainer,
                                   const string &inputPathMessage,
                                   const string &inputPathDir,
                                   const string &inputMessageSequence,
                                   const string &inputContainerSequence,
                                   double inputThreshold,
                                   int inputCoef1X,
                                   int inputCoef1Y,
                                   int inputCoef2X,
                                   int inputCoef2Y){
    /// Setup inputs
    setPathContainer(inputPathContainer);
    setContainer(); /// Setup container
    setPathMessage(inputPathMessage);
    setMessage(); /// Setup message
    setPathDir(inputPathDir);

    /// Checking if the message can be fully inserted
    if (getContainerCapacity(pathContainer) < getMessageWeight(pathMessage)){
        cout << "Container capacity is too low!\n";
        cout << "Container capacity: " << getContainerCapacity(pathContainer) << " bit(s)\n";
        cout << "Message weight: " << getMessageWeight(pathMessage) << " bit(s)\n";
        return;
    }

    /// Checking sequences' validness
    if (!setMessageSequence(inputMessageSequence)) return;
    if (!setContainerSequence(inputContainerSequence)) return;
    threshold = inputThreshold;

    /// Checking coefficients validness
    if (!setCoefs(inputCoef1X, inputCoef1Y, inputCoef2X, inputCoef2Y)) return;

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
    auto writeFileIntoContainer = [&](std::fstream &messageFile){
        const double PI = 3.14159265358979323846;

        /// Предварительное вычисление косинусных значений и нормальных коэффициентов
        double cos_t[8][8];
        double e[8][8];

        /// Вычисляем таблицу: индексы u – для частот, x – для пространственных координат.
        for (int u = 0; u < 8; u++){
            for (int x = 0; x < 8; x++){
                cos_t[u][x] = cos((2 * x + 1) * u * PI / 16);
            }
        }

        /// Вычисляем нормировку: e[u][v] = alpha(u) * alpha(v)
        for (int u = 0; u < 8; u++) {
            for (int v = 0; v < 8; v++) {
                double au = (u == 0) ? (1.0 / sqrt(8)) : 0.5;
                double av = (v == 0) ? (1.0 / sqrt(8)) : 0.5;
                e[u][v] = au * av;
            }
        }

        auto dct = [&](double dctBlock[8][8], double block[8][8]) {
            for (int u = 0; u < 8; u++) {
                for (int v = 0; v < 8; v++) {
                    double sum = 0.0;
                    for (int x = 0; x < 8; x++) {
                        for (int y = 0; y < 8; y++) {
                            sum += block[x][y] * cos_t[u][x] * cos_t[v][y];
                        }
                    }
                    dctBlock[u][v] = e[u][v] * sum;
                }
            }
        };
        auto idct = [&](double dctBlock[8][8], double block[8][8]) {
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    double sum = 0.0;
                    for (int u = 0; u < 8; u++) {
                        for (int v = 0; v < 8; v++) {
                            sum += e[u][v] * dctBlock[u][v] * cos_t[u][x] * cos_t[v][y];
                        }
                    }
                    block[x][y] = std::clamp(sum, 0.0, 255.0);
                }
            }
        };

        char messageChar;
        for (char c : containerSequence){
            switch (c){
                case 'R':{
                    for (int y = 0; y < stegocontainer.TellHeight(); y += 8){
                        for (int x = 0; x < stegocontainer.TellWidth(); x += 8){
                            if (!messageFile.get(messageChar)) return;
                            int bit = (messageChar == '1') ? 1 : 0;

                            double block[8][8];
                            for (int i = 0; i < 8; i++){
                                for (int j = 0; j < 8; j++){
                                    block[i][j] = stegocontainer(x + i, y + j)->Red;
                                }
                            }

                            double dctBlock[8][8];
                            dct(dctBlock, block);

                            double &coef1 = dctBlock[coef1Y][coef1X];
                            double &coef2 = dctBlock[coef2Y][coef2X];

                            if (bit == 0 && coef1 < coef2 + threshold) coef1 = coef2 + threshold;
                            else if (bit == 1 && coef2 < coef1 + threshold) coef2 = coef1 + threshold;

                            idct(dctBlock, block);

                            for (int i = 0; i < 8; i++){
                                for (int j = 0; j < 8; j++){
                                    stegocontainer(x + i, y + j)->Red = static_cast<unsigned char>(block[i][j]);
                                }
                            }
                        }
                    }
                    break;
                }
                case 'G':{
                    for (int y = 0; y < stegocontainer.TellHeight(); y += 8){
                        for (int x = 0; x < stegocontainer.TellWidth(); x += 8){
                            if (!messageFile.get(messageChar)) return;
                            int bit = (messageChar == '1') ? 1 : 0;

                            double block[8][8];
                            for (int i = 0; i < 8; i++){
                                for (int j = 0; j < 8; j++){
                                    block[i][j] = stegocontainer(x + i, y + j)->Green;
                                }
                            }

                            double dctBlock[8][8];
                            dct(dctBlock, block);

                            double &coef1 = dctBlock[coef1Y][coef1X];
                            double &coef2 = dctBlock[coef2Y][coef2X];

                            if (bit == 0 && coef1 < coef2 + threshold) coef1 = coef2 + threshold;
                            else if (bit == 1 && coef2 < coef1 + threshold) coef2 = coef1 + threshold;

                            idct(dctBlock, block);

                            for (int i = 0; i < 8; i++){
                                for (int j = 0; j < 8; j++){
                                    stegocontainer(x + i, y + j)->Green = static_cast<unsigned char>(block[i][j]);
                                }
                            }
                        }
                    }
                    break;
                }
                case 'B':{
                    for (int y = 0; y < stegocontainer.TellHeight(); y += 8){
                        for (int x = 0; x < stegocontainer.TellWidth(); x += 8){
                            if (!messageFile.get(messageChar)) return;
                            int bit = (messageChar == '1') ? 1 : 0;

                            double block[8][8];
                            for (int i = 0; i < 8; i++){
                                for (int j = 0; j < 8; j++){
                                    block[i][j] = stegocontainer(x + i, y + j)->Blue;
                                }
                            }

                            double dctBlock[8][8];
                            dct(dctBlock, block);

                            double &coef1 = dctBlock[coef1Y][coef1X];
                            double &coef2 = dctBlock[coef2Y][coef2X];

                            if (bit == 0 && coef1 < coef2 + threshold) coef1 = coef2 + threshold;
                            else if (bit == 1 && coef2 < coef1 + threshold) coef2 = coef1 + threshold;

                            idct(dctBlock, block);

                            for (int i = 0; i < 8; i++){
                                for (int j = 0; j < 8; j++){
                                    stegocontainer(x + i, y + j)->Blue = static_cast<unsigned char>(block[i][j]);
                                }
                            }
                        }
                    }
                    break;
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

    /// Inserting message into container
    writeFileIntoContainer(messageFile);

    messageFile.close();
    /// Creating stegocontainer picture
    stegocontainer.WriteToFile(pathStegocontainer.c_str());

    /// Deleting secondary file
    filesystem::path filepath = nameMessageFile;
    if (filesystem::exists(filepath)) filesystem::remove(filepath);
}
