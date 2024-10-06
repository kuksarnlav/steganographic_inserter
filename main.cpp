#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QDir>

#include "InserterBMP.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    auto *window = new QWidget;
    window->setWindowTitle("Stenographic inserter");
    window->showMaximized();
    QApplication::processEvents();
    window->setFixedSize(window->size());

    auto *tabWidget = new QTabWidget(window);
    auto *tab1 = new QWidget();
    auto *tab2 = new QWidget();
    tabWidget->addTab(tab1, "Creating stegocontainer");
    tabWidget->addTab(tab2, "Comparing low-bit images");

    auto *layoutContainers = new QHBoxLayout(window);
    auto *labelContainer = new QLabel;
    auto *labelStegocontainer = new QLabel;
    labelContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    labelStegocontainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    layoutContainers->addWidget(labelContainer);
    layoutContainers->addWidget(labelStegocontainer);
    auto *widgetContainers = new QWidget();
    widgetContainers->setLayout(layoutContainers);
    widgetContainers->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    auto *layoutV0 = new QVBoxLayout(window);
    auto *layoutV1 = new QVBoxLayout(window);

    auto *layoutH0 = new QHBoxLayout(window);
    auto *openContainerButton = new QPushButton("Open container (.bmp)", window);
    auto *openMsgButton = new QPushButton("Open message (.bmp)", window);
    auto *invaseMsgButton = new QPushButton("Insert message", window);
    invaseMsgButton->setEnabled(false);
    layoutH0->addWidget(openContainerButton);
    layoutH0->addWidget(openMsgButton);
    layoutH0->addWidget(invaseMsgButton);

    auto *layoutH1 = new QHBoxLayout(window);
    auto *labelMsgBits = new QLabel("Message RGB bits:");
    auto *labelMsgBitsValue = new QLabel;
    auto *labelContainerWritableBits = new QLabel("Container available RGB bits:");
    auto *labelContainerWritableBitsValue = new QLabel;
    auto *labelContainerChangedBits = new QLabel("Changed bits:");
    auto *labelContainerChangedBitsValue = new QLabel;
    auto *labelContainerChangedBitsPercentage = new QLabel("Changed bits percentage:");
    auto *labelContainerChangedBitsPercentageValue = new QLabel;
    layoutH1->addWidget(labelContainerWritableBits);
    layoutH1->addWidget(labelContainerWritableBitsValue);
    layoutH1->addWidget(labelMsgBits);
    layoutH1->addWidget(labelMsgBitsValue);
    layoutH1->addWidget(labelContainerChangedBits);
    layoutH1->addWidget(labelContainerChangedBitsValue);
    layoutH1->addWidget(labelContainerChangedBitsPercentage);
    layoutH1->addWidget(labelContainerChangedBitsPercentageValue);

    layoutV1->addLayout(layoutH0);
    layoutV1->addLayout(layoutH1);

    layoutV0->addLayout(layoutV1);
    layoutV0->addWidget(widgetContainers);

    tab1->setLayout(layoutV0);


    auto *tab2HLayout = new QHBoxLayout(window);
    auto *labelContainerLowBit = new QLabel;
    auto *labelStegocontainerLowBit = new QLabel;
    labelContainerLowBit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    labelStegocontainerLowBit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    tab2HLayout->addWidget(labelContainerLowBit);
    tab2HLayout->addWidget(labelStegocontainerLowBit);
    auto *widgetTab2 = new QWidget();
    widgetTab2->setLayout(tab2HLayout);
    widgetTab2->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    auto *labelFiller1 = new QLabel;
    auto *ButtonFiller = new QPushButton(window);
    ButtonFiller->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ButtonFiller->setEnabled(false);

    auto *layoutTab2 = new QVBoxLayout(window);
    layoutTab2->addWidget(ButtonFiller);
    layoutTab2->addWidget(labelFiller1);
    layoutTab2->addWidget(widgetTab2);


    tab2->setLayout(layoutTab2);


    auto *mainLayout = new QVBoxLayout(window);
    mainLayout->addWidget(tabWidget);


    QDir projectDirPathObject;
    std::string projectDirPath = projectDirPathObject.absolutePath().toStdString() + "/";

    InserterBMP *inserter = new InserterBMP();
    inserter->setContainerNoisePath(projectDirPath);
    inserter->setStegocontainerNoisePath(projectDirPath);
    inserter->setStegocontainerPath(projectDirPath);

    bool isContainerOpened = false, isMsgOpened = false;
    QString pathContainer = "",
        pathContainerPrevious = "",
        pathStegocontainer = "",
        pathStegocontainerPrevious = "";
    QObject::connect(openContainerButton, &QPushButton::clicked, [&pathContainer, &pathContainerPrevious, labelStegocontainer, labelContainer, invaseMsgButton, labelContainerWritableBitsValue, labelContainerChangedBitsValue,
                                                                  labelContainerChangedBitsPercentageValue, labelStegocontainerLowBit, labelContainerLowBit, &isContainerOpened, &isMsgOpened, inserter, &pathStegocontainer]{
        pathContainer = QFileDialog::getOpenFileName(nullptr,
                                               "Open .bmp container",
                                               "C:/",
                                               "Media files (*.bmp)");

        if (pathContainer != ""){
            inserter->setContainer(pathContainer.toStdString());

            if (inserter->getContainerAvailableRGBBits() == 3){
                QMessageBox errorMessageBox;
                errorMessageBox.setText("Path with non first 128 ASCII table characters is not supported!");
                std::string errorInfo = "Problem path:\n";
                errorInfo.append(pathContainer.toStdString());
                errorMessageBox.setInformativeText(errorInfo.c_str());
                errorMessageBox.setIcon(QMessageBox::Critical);
                errorMessageBox.exec();

                pathContainer = pathContainerPrevious;
            } else {
                pathContainerPrevious = pathContainer;

                labelContainerChangedBitsValue->setText("");
                labelContainerChangedBitsPercentageValue->setText("");
                labelStegocontainerLowBit->clear();
                if (invaseMsgButton->isEnabled()){
                    QPixmap pixmapMsg(pathStegocontainer);
                    labelStegocontainer->setPixmap(pixmapMsg.scaled(labelStegocontainer->size(), Qt::KeepAspectRatio));
                }

                QPixmap pixmapContainer(pathContainer);
                labelContainer->setPixmap(pixmapContainer.scaled(labelContainer->size(), Qt::KeepAspectRatio));

                inserter->setContainer(pathContainer.toStdString());
                inserter->makeContainerNoisePic();

                QPixmap pixmapContainerLowBit(QString::fromStdString(inserter->getContainerNoisePath()));
                labelContainerLowBit->setPixmap(pixmapContainerLowBit.scaled(labelContainer->size(), Qt::KeepAspectRatio));

                labelContainerWritableBitsValue->setText(QString::number(inserter->getContainerAvailableRGBBits()));


                isContainerOpened = true;
                if (isContainerOpened && isMsgOpened){
                    invaseMsgButton->setEnabled(true);
                }
            }
        }
    });

    QObject::connect(openMsgButton, &QPushButton::clicked, [&pathStegocontainer, &pathStegocontainerPrevious, labelStegocontainer, invaseMsgButton, labelMsgBitsValue,
                                                            labelContainerChangedBitsValue, labelContainerChangedBitsPercentageValue, &isMsgOpened, &isContainerOpened, inserter]{
        pathStegocontainer = QFileDialog::getOpenFileName(nullptr,
                                               "Open .bmp message",
                                               "C:/",
                                               "Media files (*.bmp)");

        if (pathStegocontainer != ""){
            inserter->setMsg(pathStegocontainer.toStdString());

            if (inserter->getMsgRGBBits() == 24){
                QMessageBox errorMessageBox;
                errorMessageBox.setText("Path with non first 128 ASCII table characters is not supported!");
                std::string errorInfo = "Problem path:\n";
                errorInfo.append(pathStegocontainer.toStdString());
                errorMessageBox.setInformativeText(errorInfo.c_str());
                errorMessageBox.setIcon(QMessageBox::Critical);
                errorMessageBox.exec();

                pathStegocontainer = pathStegocontainerPrevious;
            } else {
                pathStegocontainerPrevious = pathStegocontainer;

                labelContainerChangedBitsValue->setText("");
                labelContainerChangedBitsPercentageValue->setText("");

                QPixmap pixmapMsg(pathStegocontainer);
                labelStegocontainer->setPixmap(pixmapMsg.scaled(labelStegocontainer->size(), Qt::KeepAspectRatio));

                inserter->setMsg(pathStegocontainer.toStdString());
                labelMsgBitsValue->setText(QString::number(inserter->getMsgRGBBits()));

                isMsgOpened = true;
                if (isContainerOpened && isMsgOpened){
                    invaseMsgButton->setEnabled(true);
                }
            }
        }
    });

    QObject::connect(invaseMsgButton, &QPushButton::clicked, [labelContainerChangedBitsValue, labelContainerChangedBitsPercentageValue,
                                                              labelStegocontainer, labelStegocontainerLowBit, inserter, &pathContainer]{
        inserter->setContainer(pathContainer.toStdString());

        if (inserter->getContainerAvailableRGBBits() < inserter->getMsgRGBBits()){
            QMessageBox errorMessageBox;
            errorMessageBox.setText("Message has bigger size than the container!");
            std::string errorInfo = "Message size:\t" + std::to_string(inserter->getMsgRGBBits()) + " bits\nContainer size:\t" + std::to_string(inserter->getContainerAvailableRGBBits()) + " bits";
            errorMessageBox.setInformativeText(errorInfo.c_str());
            errorMessageBox.setIcon(QMessageBox::Critical);
            errorMessageBox.exec();
        } else {
            inserter->makeStegocontainer();

            QPixmap pixmapStegocontainer(QString::fromStdString(inserter->getStegocontainerPath()));
            labelStegocontainer->setPixmap(pixmapStegocontainer.scaled(labelStegocontainer->size(), Qt::KeepAspectRatio));

            labelContainerChangedBitsValue->setText(QString::number(inserter->getBitsChanged()));
            labelContainerChangedBitsPercentageValue->setText(QString::fromStdString(inserter->getBitsChangedPercentage()));

            inserter->makeStegocontainerNoisePic();
            QPixmap pixmapStegocontainerLowBit(QString::fromStdString(inserter->getStegocontainerNoisePath()));
            labelStegocontainerLowBit->setPixmap(pixmapStegocontainerLowBit.scaled(labelStegocontainer->size(), Qt::KeepAspectRatio));
        }
    });


    window->show();

    return a.exec();
}
