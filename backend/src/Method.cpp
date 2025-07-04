#include "Method.h"

void Method::setPathContainer(const string &path){
    pathContainer = path;
}
void Method::setPathMessage(const string &path){
    pathMessage = path;
}
void Method::setPathDir(const string &pathDir){
    pathStegocontainer = pathDir + nameStegocontainer;
}

string Method::getNameStegocontainer(){
    return nameStegocontainer;
}
string Method::getPathContainer(){
    return pathContainer;
}
string Method::getPathMessage(){
    return pathMessage;
}
string Method::getPathStegocontainer(){
    return pathStegocontainer;
}

int Method::getQuantityRGBBitsPicture(BMP &picture){
    return picture.TellHeight() * picture.TellWidth() * 3 * 8;
}


void Method::setContainer(){
    if (pathContainer.empty()){
        std::cout << "Empty container path!\n";
        return;
    }
    container.ReadFromFile(pathContainer.c_str());
}
void Method::setMessage(){
    if (pathMessage.empty()){
        std::cout << "Empty message path!\n";
        return;
    }
    message.ReadFromFile(pathMessage.c_str());
}
void Method::setStegocontainer(){
    if (pathContainer.empty()){
        std::cout << "Empty stegocontainer path!\n";
        return;
    }
    stegocontainer.ReadFromFile(pathContainer.c_str());
}

unsigned char Method::getBitsCheckedViewPicture() const{
    return bitsCheckedViewPicture;
}