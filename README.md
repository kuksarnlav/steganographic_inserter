# Steganographic Inserter


## Used Technologies & Software
- Framework: [***Qt 6.8.1***](https://www.qt.io/ "Visit Qt framework webpage")
- External library: [***EasyBMP***](https://easybmp.sourceforge.net/ "Visit library webpage")
- Build systems: CMake, QMake
- IDEs: Qt Creator, CLion 2025.1.2


## Project Properies & Structure
The current project is used as a tool for creating steganographic insertions, observing their statistical and visual properties. Program uses BMP format pictures both for container and message.
Project logically is divided into backend (folder "_backend_") and frontend parts (folder "_steganographic_inserter_").

Backend part consists of several classes:
- Method (MethodLSB, MethodKutter, MethodZhaoKoch). Used for making steganographic insertion with mentioned methods.
- Statistics. Used for statistical analysis (Percent ratio of 1 bits to all bits of container, message, stegocontainer; Percent ratio of changed container bits to all stegocontainer bits) of insertion.
- Viewer. Used for visual analysis (Combination of color channels and bit planes) of insertion.

Frontend part consists of mainwindows class and created UI in mainform.ui.

Project already has downloaded and unarchived EasyBMP library without example project for lighter project size.

## GUI

GUI of the program is single window with 3 tabs.

### Tabs:

### Buttons:

## Installation & Running
