# Steganographic Inserter


## Used Technologies & Software
- Framework: [***Qt 6.8.1***](https://www.qt.io/ "Visit Qt framework webpage")
- External library: [***EasyBMP***](https://easybmp.sourceforge.net/ "Visit library webpage")
- Build systems: CMake, QMake
- IDEs: Qt Creator, CLion 2025.1.2


## Project Properies & Structure
The current project is used as a tool for creating steganographic insertions, observing their statistical and visual properties.
Program uses BMP format pictures both for container and message.
Due to the OOP structure of the project it can be easily presented as a scheme with modules, which is shown on the picture right below.

Project logically is divided into backend (folder "_backend_") and frontend parts (folder "_steganographic_inserter_").

Backend part consists of several classes:
- Method (MethodLSB, MethodKutter, MethodZhaoKoch). Used for making steganographic insertion with mentioned methods.
- Statistics. Used for statistical analysis (Percent ratio of 1 bits to all bits of container, message, stegocontainer; Percent ratio of changed container bits to all stegocontainer bits) of insertion.
- Viewer. Used for visual analysis (Combination of color channels and bit planes) of insertion.

Frontend part consists of mainwindows class and created UI in mainform.ui.

Project already has downloaded and unarchived EasyBMP library without example project for lighter project size.

## GUI

### Menu

Menu has 2 options:
- "Files". For uploading images into the app.
  - "Upload container (.BMP)"
  - "Upload message (.BMP)"
  - "Upload view image (.BMP)"
- "Methods". For choosing an insertion method.
  - "LSB"
    - "Consecutive". Forms sequence of message color channels and inserts all these bits consecutive into sequence of container color channels.
    - "Separate". Inserts by the principle message color channel into container color channel.
  - "Kutter".
  - "Zhao-Koch".

### Tabs

GUI of the program is single window with 3 tabs:
- "Message and Container". Used for inserting message into container, choosing method settings.
- "Stegocontaienr and Statistics". Used for viewing statistics and stegocontainer.
- "View". Used for visual analysis of stegocontainer color channels and bit planes.

## Installation & Running

1. [***Download ZIP Archive***](https://github.com/kuksarnlav/stenographic_inserter/archive/refs/heads/main.zip "Download stenographic inserter") of the project
2. Unpack the archive into your folder destination

### Console program

Current instruction is about installation and running the program in CLion IDE.

3. Open stenographic_inserter_backend folder via CLion
4. Click OK in Open Project Wizard window
5. After that actions you would be able to run project as usual (don't forget to enter your own .bmp files' paths in main.cpp of backend project, otherwise error will happen)

### GUI program

Current instruction is about installation and running the program in Qt Creator.

3. Open stenographic_inserter.pro file via Qt Creator
4. Choose Desktop Qt 6.8.1 MinGW 64-bit compiler in ***Configure Project*** section, click ***Configure Project***
5. After that actions you would be able to run project as usual

### App

3. Double click ***steganographic_inserter.exe*** in ***steganographic_inserter_app*** folder
