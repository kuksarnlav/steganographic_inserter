#include <iostream>
#include "InserterBMP.h"

int main(){
    InserterBMP inserter;
    inserter.setContainer("D:/sample2.bmp");
    inserter.setMsg("D:/image.bmp");
    inserter.setStegocontainerPath("D:/");
    inserter.setContainerNoisePath("D:/");
    inserter.setStegocontainerNoisePath("D:/");
    std::cout << inserter.getContainerPath() << ' ' << inserter.getMsgPath() << '\n';
    std::cout << inserter.getContainerAvailableRGBBits() << ' ' << inserter.getMsgRGBBits() << '\n';
    inserter.makeStegocontainer();
    inserter.makeContainerNoisePic();
    inserter.makeStegocontainerNoisePic();
    std::cout << inserter.getContainerNoisePath() << ' ' << inserter.getStegocontainerNoisePath() << ' ' << inserter.getStegocontainerPath() << '\n';
    std::cout << inserter.getBitsChanged() << ' ' << inserter.getBitsChangedPercentage() << '\n';
    return 0;
}