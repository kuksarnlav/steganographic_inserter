#include "Viewer.h"
#include <vector>
#include <algorithm>

bool Viewer::setViewBits(const vector<int> &bits){
    /// empty picture can't be viewed
    if (bits.empty()){
        cout << "Empty picture can't be viewed!\n";
        return false;
    }

    /// maximum allowed size check
    if (bits.size() > 8){
        cout << "There are only 8 positions in byte!\n";
        return false;
    }

    /// bit numbers must be >= 0 and <= 7
    for (int bitN : bits){
        if (bitN < 0 || bitN > 7){
            cout << "Bit numbers must be >= 0 and <= 7!\n";
            return false;
        }
    }

    viewBits = bits;

    /// standard order
    sort(viewBits.begin(), viewBits.end(), greater<>());

    return true;
}
void Viewer::setImagePath(const string &path){
    /// correct input required
    pathToImage = path;
}
void Viewer::setExportPath(const string &path){
    /// correct input required
    pathExport = path;
}
bool Viewer::setColorChannels(const string &inputViewChannels){
    if (inputViewChannels.empty()) return false;
    string temp;
    if (inputViewChannels.find('R') != std::string::npos) temp += 'R';
    if (inputViewChannels.find('G') != std::string::npos) temp += 'G';
    if (inputViewChannels.find('B') != std::string::npos) temp += 'B';
    viewChannels = temp;
    return true;
}


void Viewer::createView(vector<int> &bits, const string &inputPathToImage, const string &inputPathExport, const string &inputViewChannels){
    /// empty picture can't be viewed
    if (!setViewBits(bits)) return;
    /// no colors can't be viewed
    if (!setColorChannels(inputViewChannels)) return;

    /// initialization of paths
    setImagePath(inputPathToImage);
    setExportPath(inputPathExport);

    /// uploading image
    image.ReadFromFile(pathToImage.c_str());

    /// creating view image
    for (char color : viewChannels){
        switch (color){
            case 'R': {
                for (int y = 0; y < image.TellHeight(); y++){
                    for (int x = 0; x < image.TellWidth(); x++){
                        RGBApixel *pPixel = image(x, y);

                        unsigned char rByteMem = 0b0000'0000;
                        for (size_t i = 0; i < viewBits.size(); i++){
                            unsigned char rByte = pPixel->Red << (7 - viewBits[i]);
                            rByte &= 0b1000'0000;
                            rByte >>= i;
                            rByteMem |= rByte;
                        }

                        pPixel->Red = rByteMem;
                    }
                }
                break;
            }
            case 'G': {
                for (int y = 0; y < image.TellHeight(); y++){
                    for (int x = 0; x < image.TellWidth(); x++){
                        RGBApixel *pPixel = image(x, y);

                        unsigned char gByteMem = 0b0000'0000;
                        for (size_t i = 0; i < viewBits.size(); i++){
                            unsigned char gByte = pPixel->Green << (7 - viewBits[i]);
                            gByte &= 0b1000'0000;
                            gByte >>= i;
                            gByteMem |= gByte;
                        }

                        pPixel->Green = gByteMem;
                    }
                }
                break;
            }
            case 'B': {
                for (int y = 0; y < image.TellHeight(); y++){
                    for (int x = 0; x < image.TellWidth(); x++){
                        RGBApixel *pPixel = image(x, y);

                        unsigned char bByteMem = 0b0000'0000;
                        for (size_t i = 0; i < viewBits.size(); i++){
                            unsigned char bByte = pPixel->Blue << (7 - viewBits[i]);
                            bByte &= 0b1000'0000;
                            bByte >>= i;
                            bByteMem |= bByte;
                        }

                        pPixel->Blue = bByteMem;
                    }
                }
                break;
            }
            default: break;
        }
    }
    if (inputViewChannels.find('R') == std::string::npos){
        for (int y = 0; y < image.TellHeight(); y++){
            for (int x = 0; x < image.TellWidth(); x++){
                RGBApixel *pPixel = image(x, y);
                pPixel->Red = 0b0000'0000;
            }
        }
    }
    if (inputViewChannels.find('G') == std::string::npos){
        for (int y = 0; y < image.TellHeight(); y++){
            for (int x = 0; x < image.TellWidth(); x++){
                RGBApixel *pPixel = image(x, y);
                pPixel->Green = 0b0000'0000;
            }
        }
    }
    if (inputViewChannels.find('B') == std::string::npos){
        for (int y = 0; y < image.TellHeight(); y++){
            for (int x = 0; x < image.TellWidth(); x++){
                RGBApixel *pPixel = image(x, y);
                pPixel->Blue = 0b0000'0000;
            }
        }
    }

    /// exporting image
    image.WriteToFile((pathExport + nameImageView).c_str());
}