#include "EasyBMP.h"

class InserterBMP{
public:
    void setContainer(std::string containerPath);
    void setMsg(std::string msgPath);
    void setStegocontainerPath(std::string directoryPath);
    void setContainerNoisePath(std::string directoryPath);
    void setStegocontainerNoisePath(std::string directoryPath);

    size_t getBitsChanged();
    size_t getContainerAvailableRGBBits();
    size_t getMsgRGBBits();
    std::string getContainerPath();
    std::string getMsgPath();
    std::string getContainerNoisePath();
    std::string getStegocontainerPath();
    std::string getStegocontainerNoisePath();
    std::string getBitsChangedPercentage();

    void makeStegocontainer();
    void makeContainerNoisePic();
    void makeStegocontainerNoisePic();
private:
    BMP container;
    BMP msg;
    std::string containerPath;
    std::string msgPath;
    std::string containerNoisePath;
    std::string stegocontainerPath;
    std::string stegocontainerNoisePath;
    std::string stegocontainerFileName = "stegocontainer.bmp";
    std::string containerNoiseFileName = "noiseContainer.bmp";
    std::string stegocontainerNoiseFileName = "noiseStegocontainer.bmp";
    size_t bitsChanged = 0;
};