#pragma once

#include "EasyBMP.h"
#include <string>
#include <vector>

using namespace std;

class Viewer{
public:
    void createView(vector<int> &bits, const string &inputPathToImage, const string &inputPathExport, const string &inputViewChannels);

    string getPathViewedImage(){
        return pathExport + "/" + nameImageView;
    }

protected:
    const string nameImageView = "viewImage.bmp"; /// view image name
    string pathExport; /// export path
    string pathToImage; /// image for viewing path
    vector<int> viewBits; /// checked bit planes
    string viewChannels; /// Color channels
    BMP image;

    bool setViewBits (const vector<int> &viewBits);
    void setImagePath (const string &path);
    void setExportPath (const string &path);
    bool setColorChannels (const string &inputViewChannels);
};