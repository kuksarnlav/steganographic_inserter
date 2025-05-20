/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionUploadContainer;
    QAction *actionUploadMessage;
    QAction *actionMethodKutter;
    QAction *actionMethodZhaoKoch;
    QAction *actionModeInsertion;
    QAction *actionModeExtraction;
    QAction *actionMethodLSBConsecutive;
    QAction *actionMethodLSBSeparate;
    QAction *actionCipherRSA;
    QAction *actionCipherDES;
    QAction *actionCipherAES;
    QAction *actionCipherGOST_28147_89;
    QAction *actionCipherNone;
    QAction *actionUploadViewImage;
    QAction *actionSaveViewImage;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hLayoutMethodLSB;
    QVBoxLayout *vLayoutLSBVariant;
    QHBoxLayout *hLayoutMethodLSBSep;
    QLabel *labelSep;
    QComboBox *comboBoxSepContainer1;
    QLabel *labelSepArrow1;
    QComboBox *comboBoxSepMessage1;
    QLabel *labelSepComma1;
    QComboBox *comboBoxSepContainer2;
    QLabel *labelSepArrow2;
    QComboBox *comboBoxSepMessage2;
    QLabel *labelSepComma2;
    QComboBox *comboBoxSepContainer3;
    QLabel *labelSepArrow3;
    QComboBox *comboBoxSepMessage3;
    QHBoxLayout *hLayoutMethodLSBCon;
    QLabel *labelConContainer;
    QComboBox *comboBoxConContainer1;
    QComboBox *comboBoxConContainer2;
    QComboBox *comboBoxConContainer3;
    QLabel *labelArrow;
    QLabel *labelConMessage;
    QComboBox *comboBoxConMessage1;
    QComboBox *comboBoxConMessage2;
    QComboBox *comboBoxConMessage3;
    QHBoxLayout *hLayoutMethodLSBBits;
    QLabel *labelLSBBits;
    QCheckBox *checkBox7;
    QCheckBox *checkBox6;
    QCheckBox *checkBox5;
    QCheckBox *checkBox4;
    QCheckBox *checkBox3;
    QCheckBox *checkBox2;
    QCheckBox *checkBox1;
    QCheckBox *checkBox0;
    QHBoxLayout *hLayoutMethodKutter;
    QLabel *labelKutter;
    QHBoxLayout *hLayoutMethodZhaoKoch;
    QLabel *labelZhaoKoch;
    QHBoxLayout *hLayoutButtons;
    QPushButton *pushButtonInsert;
    QPushButton *pushButtonExtract;
    QHBoxLayout *hLayoutContainerMessage;
    QLabel *labelContainer;
    QLabel *labelMessage;
    QWidget *tab2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *hLayoutViewBit;
    QSpacerItem *hSpacerLeft;
    QLabel *labelViewOnePlane;
    QCheckBox *checkBoxView7;
    QCheckBox *checkBoxView6;
    QCheckBox *checkBoxView5;
    QCheckBox *checkBoxView4;
    QCheckBox *checkBoxView3;
    QCheckBox *checkBoxView2;
    QCheckBox *checkBoxView1;
    QCheckBox *checkBoxView0;
    QSpacerItem *hSpacerRight;
    QLabel *labelView;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuMethods;
    QMenu *menuLSB;
    QMenu *menuModes;
    QMenu *menuEncryption;
    QMenu *menuAsymmetric;
    QMenu *menuSymmetric;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1368, 626);
        actionUploadContainer = new QAction(MainWindow);
        actionUploadContainer->setObjectName("actionUploadContainer");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        actionUploadContainer->setIcon(icon);
        actionUploadMessage = new QAction(MainWindow);
        actionUploadMessage->setObjectName("actionUploadMessage");
        actionUploadMessage->setIcon(icon);
        actionMethodKutter = new QAction(MainWindow);
        actionMethodKutter->setObjectName("actionMethodKutter");
        actionMethodKutter->setCheckable(true);
        actionMethodZhaoKoch = new QAction(MainWindow);
        actionMethodZhaoKoch->setObjectName("actionMethodZhaoKoch");
        actionMethodZhaoKoch->setCheckable(true);
        actionModeInsertion = new QAction(MainWindow);
        actionModeInsertion->setObjectName("actionModeInsertion");
        actionModeInsertion->setCheckable(true);
        actionModeInsertion->setChecked(true);
        actionModeExtraction = new QAction(MainWindow);
        actionModeExtraction->setObjectName("actionModeExtraction");
        actionModeExtraction->setCheckable(true);
        actionMethodLSBConsecutive = new QAction(MainWindow);
        actionMethodLSBConsecutive->setObjectName("actionMethodLSBConsecutive");
        actionMethodLSBConsecutive->setCheckable(true);
        actionMethodLSBConsecutive->setChecked(true);
        actionMethodLSBSeparate = new QAction(MainWindow);
        actionMethodLSBSeparate->setObjectName("actionMethodLSBSeparate");
        actionMethodLSBSeparate->setCheckable(true);
        actionCipherRSA = new QAction(MainWindow);
        actionCipherRSA->setObjectName("actionCipherRSA");
        actionCipherRSA->setCheckable(true);
        actionCipherDES = new QAction(MainWindow);
        actionCipherDES->setObjectName("actionCipherDES");
        actionCipherDES->setCheckable(true);
        actionCipherAES = new QAction(MainWindow);
        actionCipherAES->setObjectName("actionCipherAES");
        actionCipherAES->setCheckable(true);
        actionCipherGOST_28147_89 = new QAction(MainWindow);
        actionCipherGOST_28147_89->setObjectName("actionCipherGOST_28147_89");
        actionCipherGOST_28147_89->setCheckable(true);
        actionCipherNone = new QAction(MainWindow);
        actionCipherNone->setObjectName("actionCipherNone");
        actionCipherNone->setCheckable(true);
        actionCipherNone->setChecked(true);
        actionUploadViewImage = new QAction(MainWindow);
        actionUploadViewImage->setObjectName("actionUploadViewImage");
        actionUploadViewImage->setIcon(icon);
        actionSaveViewImage = new QAction(MainWindow);
        actionSaveViewImage->setObjectName("actionSaveViewImage");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        actionSaveViewImage->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        verticalLayout = new QVBoxLayout(tab1);
        verticalLayout->setObjectName("verticalLayout");
        hLayoutMethodLSB = new QHBoxLayout();
        hLayoutMethodLSB->setObjectName("hLayoutMethodLSB");
        vLayoutLSBVariant = new QVBoxLayout();
        vLayoutLSBVariant->setObjectName("vLayoutLSBVariant");
        hLayoutMethodLSBSep = new QHBoxLayout();
        hLayoutMethodLSBSep->setObjectName("hLayoutMethodLSBSep");
        labelSep = new QLabel(tab1);
        labelSep->setObjectName("labelSep");

        hLayoutMethodLSBSep->addWidget(labelSep);

        comboBoxSepContainer1 = new QComboBox(tab1);
        comboBoxSepContainer1->addItem(QString());
        comboBoxSepContainer1->addItem(QString());
        comboBoxSepContainer1->addItem(QString());
        comboBoxSepContainer1->addItem(QString());
        comboBoxSepContainer1->setObjectName("comboBoxSepContainer1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxSepContainer1->sizePolicy().hasHeightForWidth());
        comboBoxSepContainer1->setSizePolicy(sizePolicy);
        comboBoxSepContainer1->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBSep->addWidget(comboBoxSepContainer1);

        labelSepArrow1 = new QLabel(tab1);
        labelSepArrow1->setObjectName("labelSepArrow1");
        labelSepArrow1->setMaximumSize(QSize(10, 16777215));
        labelSepArrow1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        hLayoutMethodLSBSep->addWidget(labelSepArrow1);

        comboBoxSepMessage1 = new QComboBox(tab1);
        comboBoxSepMessage1->addItem(QString());
        comboBoxSepMessage1->addItem(QString());
        comboBoxSepMessage1->addItem(QString());
        comboBoxSepMessage1->addItem(QString());
        comboBoxSepMessage1->setObjectName("comboBoxSepMessage1");
        sizePolicy.setHeightForWidth(comboBoxSepMessage1->sizePolicy().hasHeightForWidth());
        comboBoxSepMessage1->setSizePolicy(sizePolicy);
        comboBoxSepMessage1->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBSep->addWidget(comboBoxSepMessage1);

        labelSepComma1 = new QLabel(tab1);
        labelSepComma1->setObjectName("labelSepComma1");
        labelSepComma1->setMaximumSize(QSize(5, 16777215));

        hLayoutMethodLSBSep->addWidget(labelSepComma1);

        comboBoxSepContainer2 = new QComboBox(tab1);
        comboBoxSepContainer2->addItem(QString());
        comboBoxSepContainer2->addItem(QString());
        comboBoxSepContainer2->addItem(QString());
        comboBoxSepContainer2->addItem(QString());
        comboBoxSepContainer2->setObjectName("comboBoxSepContainer2");
        sizePolicy.setHeightForWidth(comboBoxSepContainer2->sizePolicy().hasHeightForWidth());
        comboBoxSepContainer2->setSizePolicy(sizePolicy);
        comboBoxSepContainer2->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBSep->addWidget(comboBoxSepContainer2);

        labelSepArrow2 = new QLabel(tab1);
        labelSepArrow2->setObjectName("labelSepArrow2");
        labelSepArrow2->setMaximumSize(QSize(10, 16777215));
        labelSepArrow2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        hLayoutMethodLSBSep->addWidget(labelSepArrow2);

        comboBoxSepMessage2 = new QComboBox(tab1);
        comboBoxSepMessage2->addItem(QString());
        comboBoxSepMessage2->addItem(QString());
        comboBoxSepMessage2->addItem(QString());
        comboBoxSepMessage2->addItem(QString());
        comboBoxSepMessage2->setObjectName("comboBoxSepMessage2");
        sizePolicy.setHeightForWidth(comboBoxSepMessage2->sizePolicy().hasHeightForWidth());
        comboBoxSepMessage2->setSizePolicy(sizePolicy);
        comboBoxSepMessage2->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBSep->addWidget(comboBoxSepMessage2);

        labelSepComma2 = new QLabel(tab1);
        labelSepComma2->setObjectName("labelSepComma2");
        labelSepComma2->setMaximumSize(QSize(5, 16777215));

        hLayoutMethodLSBSep->addWidget(labelSepComma2);

        comboBoxSepContainer3 = new QComboBox(tab1);
        comboBoxSepContainer3->addItem(QString());
        comboBoxSepContainer3->addItem(QString());
        comboBoxSepContainer3->addItem(QString());
        comboBoxSepContainer3->addItem(QString());
        comboBoxSepContainer3->setObjectName("comboBoxSepContainer3");
        sizePolicy.setHeightForWidth(comboBoxSepContainer3->sizePolicy().hasHeightForWidth());
        comboBoxSepContainer3->setSizePolicy(sizePolicy);
        comboBoxSepContainer3->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBSep->addWidget(comboBoxSepContainer3);

        labelSepArrow3 = new QLabel(tab1);
        labelSepArrow3->setObjectName("labelSepArrow3");
        labelSepArrow3->setMaximumSize(QSize(10, 16777215));
        labelSepArrow3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        hLayoutMethodLSBSep->addWidget(labelSepArrow3);

        comboBoxSepMessage3 = new QComboBox(tab1);
        comboBoxSepMessage3->addItem(QString());
        comboBoxSepMessage3->addItem(QString());
        comboBoxSepMessage3->addItem(QString());
        comboBoxSepMessage3->addItem(QString());
        comboBoxSepMessage3->setObjectName("comboBoxSepMessage3");
        sizePolicy.setHeightForWidth(comboBoxSepMessage3->sizePolicy().hasHeightForWidth());
        comboBoxSepMessage3->setSizePolicy(sizePolicy);
        comboBoxSepMessage3->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBSep->addWidget(comboBoxSepMessage3);


        vLayoutLSBVariant->addLayout(hLayoutMethodLSBSep);

        hLayoutMethodLSBCon = new QHBoxLayout();
        hLayoutMethodLSBCon->setObjectName("hLayoutMethodLSBCon");
        labelConContainer = new QLabel(tab1);
        labelConContainer->setObjectName("labelConContainer");
        labelConContainer->setScaledContents(false);
        labelConContainer->setAlignment(Qt::AlignmentFlag::AlignCenter);

        hLayoutMethodLSBCon->addWidget(labelConContainer);

        comboBoxConContainer1 = new QComboBox(tab1);
        comboBoxConContainer1->addItem(QString());
        comboBoxConContainer1->addItem(QString());
        comboBoxConContainer1->addItem(QString());
        comboBoxConContainer1->addItem(QString());
        comboBoxConContainer1->setObjectName("comboBoxConContainer1");
        comboBoxConContainer1->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBCon->addWidget(comboBoxConContainer1);

        comboBoxConContainer2 = new QComboBox(tab1);
        comboBoxConContainer2->addItem(QString());
        comboBoxConContainer2->addItem(QString());
        comboBoxConContainer2->addItem(QString());
        comboBoxConContainer2->addItem(QString());
        comboBoxConContainer2->setObjectName("comboBoxConContainer2");
        comboBoxConContainer2->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBCon->addWidget(comboBoxConContainer2);

        comboBoxConContainer3 = new QComboBox(tab1);
        comboBoxConContainer3->addItem(QString());
        comboBoxConContainer3->addItem(QString());
        comboBoxConContainer3->addItem(QString());
        comboBoxConContainer3->addItem(QString());
        comboBoxConContainer3->setObjectName("comboBoxConContainer3");
        comboBoxConContainer3->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBCon->addWidget(comboBoxConContainer3);

        labelArrow = new QLabel(tab1);
        labelArrow->setObjectName("labelArrow");
        labelArrow->setMinimumSize(QSize(10, 0));
        labelArrow->setMaximumSize(QSize(16777215, 16777215));
        labelArrow->setAlignment(Qt::AlignmentFlag::AlignCenter);

        hLayoutMethodLSBCon->addWidget(labelArrow);

        labelConMessage = new QLabel(tab1);
        labelConMessage->setObjectName("labelConMessage");
        labelConMessage->setAlignment(Qt::AlignmentFlag::AlignCenter);

        hLayoutMethodLSBCon->addWidget(labelConMessage);

        comboBoxConMessage1 = new QComboBox(tab1);
        comboBoxConMessage1->addItem(QString());
        comboBoxConMessage1->addItem(QString());
        comboBoxConMessage1->addItem(QString());
        comboBoxConMessage1->addItem(QString());
        comboBoxConMessage1->setObjectName("comboBoxConMessage1");
        comboBoxConMessage1->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBCon->addWidget(comboBoxConMessage1);

        comboBoxConMessage2 = new QComboBox(tab1);
        comboBoxConMessage2->addItem(QString());
        comboBoxConMessage2->addItem(QString());
        comboBoxConMessage2->addItem(QString());
        comboBoxConMessage2->addItem(QString());
        comboBoxConMessage2->setObjectName("comboBoxConMessage2");
        comboBoxConMessage2->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBCon->addWidget(comboBoxConMessage2);

        comboBoxConMessage3 = new QComboBox(tab1);
        comboBoxConMessage3->addItem(QString());
        comboBoxConMessage3->addItem(QString());
        comboBoxConMessage3->addItem(QString());
        comboBoxConMessage3->addItem(QString());
        comboBoxConMessage3->setObjectName("comboBoxConMessage3");
        comboBoxConMessage3->setMinimumSize(QSize(40, 0));

        hLayoutMethodLSBCon->addWidget(comboBoxConMessage3);


        vLayoutLSBVariant->addLayout(hLayoutMethodLSBCon);


        hLayoutMethodLSB->addLayout(vLayoutLSBVariant);

        hLayoutMethodLSBBits = new QHBoxLayout();
        hLayoutMethodLSBBits->setObjectName("hLayoutMethodLSBBits");
        labelLSBBits = new QLabel(tab1);
        labelLSBBits->setObjectName("labelLSBBits");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelLSBBits->sizePolicy().hasHeightForWidth());
        labelLSBBits->setSizePolicy(sizePolicy1);

        hLayoutMethodLSBBits->addWidget(labelLSBBits);

        checkBox7 = new QCheckBox(tab1);
        checkBox7->setObjectName("checkBox7");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox7->sizePolicy().hasHeightForWidth());
        checkBox7->setSizePolicy(sizePolicy2);
        checkBox7->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBox7->setAutoFillBackground(false);
        checkBox7->setAutoExclusive(false);

        hLayoutMethodLSBBits->addWidget(checkBox7);

        checkBox6 = new QCheckBox(tab1);
        checkBox6->setObjectName("checkBox6");
        sizePolicy2.setHeightForWidth(checkBox6->sizePolicy().hasHeightForWidth());
        checkBox6->setSizePolicy(sizePolicy2);
        checkBox6->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox6);

        checkBox5 = new QCheckBox(tab1);
        checkBox5->setObjectName("checkBox5");
        sizePolicy2.setHeightForWidth(checkBox5->sizePolicy().hasHeightForWidth());
        checkBox5->setSizePolicy(sizePolicy2);
        checkBox5->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox5);

        checkBox4 = new QCheckBox(tab1);
        checkBox4->setObjectName("checkBox4");
        sizePolicy2.setHeightForWidth(checkBox4->sizePolicy().hasHeightForWidth());
        checkBox4->setSizePolicy(sizePolicy2);
        checkBox4->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox4);

        checkBox3 = new QCheckBox(tab1);
        checkBox3->setObjectName("checkBox3");
        sizePolicy2.setHeightForWidth(checkBox3->sizePolicy().hasHeightForWidth());
        checkBox3->setSizePolicy(sizePolicy2);
        checkBox3->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox3);

        checkBox2 = new QCheckBox(tab1);
        checkBox2->setObjectName("checkBox2");
        sizePolicy2.setHeightForWidth(checkBox2->sizePolicy().hasHeightForWidth());
        checkBox2->setSizePolicy(sizePolicy2);
        checkBox2->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox2);

        checkBox1 = new QCheckBox(tab1);
        checkBox1->setObjectName("checkBox1");
        sizePolicy2.setHeightForWidth(checkBox1->sizePolicy().hasHeightForWidth());
        checkBox1->setSizePolicy(sizePolicy2);
        checkBox1->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox1);

        checkBox0 = new QCheckBox(tab1);
        checkBox0->setObjectName("checkBox0");
        sizePolicy2.setHeightForWidth(checkBox0->sizePolicy().hasHeightForWidth());
        checkBox0->setSizePolicy(sizePolicy2);
        checkBox0->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        hLayoutMethodLSBBits->addWidget(checkBox0);


        hLayoutMethodLSB->addLayout(hLayoutMethodLSBBits);


        verticalLayout->addLayout(hLayoutMethodLSB);

        hLayoutMethodKutter = new QHBoxLayout();
        hLayoutMethodKutter->setObjectName("hLayoutMethodKutter");
        labelKutter = new QLabel(tab1);
        labelKutter->setObjectName("labelKutter");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelKutter->sizePolicy().hasHeightForWidth());
        labelKutter->setSizePolicy(sizePolicy3);

        hLayoutMethodKutter->addWidget(labelKutter, 0, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout->addLayout(hLayoutMethodKutter);

        hLayoutMethodZhaoKoch = new QHBoxLayout();
        hLayoutMethodZhaoKoch->setObjectName("hLayoutMethodZhaoKoch");
        labelZhaoKoch = new QLabel(tab1);
        labelZhaoKoch->setObjectName("labelZhaoKoch");
        sizePolicy3.setHeightForWidth(labelZhaoKoch->sizePolicy().hasHeightForWidth());
        labelZhaoKoch->setSizePolicy(sizePolicy3);

        hLayoutMethodZhaoKoch->addWidget(labelZhaoKoch, 0, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout->addLayout(hLayoutMethodZhaoKoch);

        hLayoutButtons = new QHBoxLayout();
        hLayoutButtons->setObjectName("hLayoutButtons");
        pushButtonInsert = new QPushButton(tab1);
        pushButtonInsert->setObjectName("pushButtonInsert");
        pushButtonInsert->setEnabled(false);
        pushButtonInsert->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        hLayoutButtons->addWidget(pushButtonInsert);

        pushButtonExtract = new QPushButton(tab1);
        pushButtonExtract->setObjectName("pushButtonExtract");
        pushButtonExtract->setEnabled(false);

        hLayoutButtons->addWidget(pushButtonExtract);


        verticalLayout->addLayout(hLayoutButtons);

        hLayoutContainerMessage = new QHBoxLayout();
        hLayoutContainerMessage->setObjectName("hLayoutContainerMessage");
        labelContainer = new QLabel(tab1);
        labelContainer->setObjectName("labelContainer");
        labelContainer->setMinimumSize(QSize(200, 200));

        hLayoutContainerMessage->addWidget(labelContainer);

        labelMessage = new QLabel(tab1);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setMinimumSize(QSize(200, 200));

        hLayoutContainerMessage->addWidget(labelMessage);


        verticalLayout->addLayout(hLayoutContainerMessage);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        verticalLayout_3 = new QVBoxLayout(tab2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        hLayoutViewBit = new QHBoxLayout();
        hLayoutViewBit->setObjectName("hLayoutViewBit");
        hLayoutViewBit->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        hSpacerLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutViewBit->addItem(hSpacerLeft);

        labelViewOnePlane = new QLabel(tab2);
        labelViewOnePlane->setObjectName("labelViewOnePlane");
        labelViewOnePlane->setEnabled(true);

        hLayoutViewBit->addWidget(labelViewOnePlane);

        checkBoxView7 = new QCheckBox(tab2);
        checkBoxView7->setObjectName("checkBoxView7");
        checkBoxView7->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView7->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView7);

        checkBoxView6 = new QCheckBox(tab2);
        checkBoxView6->setObjectName("checkBoxView6");
        sizePolicy2.setHeightForWidth(checkBoxView6->sizePolicy().hasHeightForWidth());
        checkBoxView6->setSizePolicy(sizePolicy2);
        checkBoxView6->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView6->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView6);

        checkBoxView5 = new QCheckBox(tab2);
        checkBoxView5->setObjectName("checkBoxView5");
        sizePolicy2.setHeightForWidth(checkBoxView5->sizePolicy().hasHeightForWidth());
        checkBoxView5->setSizePolicy(sizePolicy2);
        checkBoxView5->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView5->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView5);

        checkBoxView4 = new QCheckBox(tab2);
        checkBoxView4->setObjectName("checkBoxView4");
        sizePolicy2.setHeightForWidth(checkBoxView4->sizePolicy().hasHeightForWidth());
        checkBoxView4->setSizePolicy(sizePolicy2);
        checkBoxView4->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView4->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView4);

        checkBoxView3 = new QCheckBox(tab2);
        checkBoxView3->setObjectName("checkBoxView3");
        sizePolicy2.setHeightForWidth(checkBoxView3->sizePolicy().hasHeightForWidth());
        checkBoxView3->setSizePolicy(sizePolicy2);
        checkBoxView3->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView3->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView3);

        checkBoxView2 = new QCheckBox(tab2);
        checkBoxView2->setObjectName("checkBoxView2");
        sizePolicy2.setHeightForWidth(checkBoxView2->sizePolicy().hasHeightForWidth());
        checkBoxView2->setSizePolicy(sizePolicy2);
        checkBoxView2->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView2->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView2);

        checkBoxView1 = new QCheckBox(tab2);
        checkBoxView1->setObjectName("checkBoxView1");
        sizePolicy2.setHeightForWidth(checkBoxView1->sizePolicy().hasHeightForWidth());
        checkBoxView1->setSizePolicy(sizePolicy2);
        checkBoxView1->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView1->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView1);

        checkBoxView0 = new QCheckBox(tab2);
        checkBoxView0->setObjectName("checkBoxView0");
        sizePolicy2.setHeightForWidth(checkBoxView0->sizePolicy().hasHeightForWidth());
        checkBoxView0->setSizePolicy(sizePolicy2);
        checkBoxView0->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        checkBoxView0->setChecked(true);

        hLayoutViewBit->addWidget(checkBoxView0);

        hSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hLayoutViewBit->addItem(hSpacerRight);


        verticalLayout_3->addLayout(hLayoutViewBit);

        labelView = new QLabel(tab2);
        labelView->setObjectName("labelView");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelView->sizePolicy().hasHeightForWidth());
        labelView->setSizePolicy(sizePolicy4);

        verticalLayout_3->addWidget(labelView);

        tabWidget->addTab(tab2, QString());

        horizontalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1368, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menuMethods = new QMenu(menubar);
        menuMethods->setObjectName("menuMethods");
        menuLSB = new QMenu(menuMethods);
        menuLSB->setObjectName("menuLSB");
        menuModes = new QMenu(menubar);
        menuModes->setObjectName("menuModes");
        menuEncryption = new QMenu(menubar);
        menuEncryption->setObjectName("menuEncryption");
        menuAsymmetric = new QMenu(menuEncryption);
        menuAsymmetric->setObjectName("menuAsymmetric");
        menuSymmetric = new QMenu(menuEncryption);
        menuSymmetric->setObjectName("menuSymmetric");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuModes->menuAction());
        menubar->addAction(menuMethods->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menuEncryption->menuAction());
        menu->addAction(actionUploadContainer);
        menu->addAction(actionUploadMessage);
        menu->addSeparator();
        menu->addAction(actionUploadViewImage);
        menu->addAction(actionSaveViewImage);
        menuMethods->addAction(menuLSB->menuAction());
        menuMethods->addAction(actionMethodKutter);
        menuMethods->addAction(actionMethodZhaoKoch);
        menuLSB->addAction(actionMethodLSBConsecutive);
        menuLSB->addAction(actionMethodLSBSeparate);
        menuModes->addAction(actionModeInsertion);
        menuModes->addAction(actionModeExtraction);
        menuEncryption->addAction(actionCipherNone);
        menuEncryption->addAction(menuSymmetric->menuAction());
        menuEncryption->addAction(menuAsymmetric->menuAction());
        menuAsymmetric->addAction(actionCipherRSA);
        menuSymmetric->addAction(actionCipherDES);
        menuSymmetric->addAction(actionCipherAES);
        menuSymmetric->addAction(actionCipherGOST_28147_89);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionUploadContainer->setText(QCoreApplication::translate("MainWindow", "Upload container (.BMP)", nullptr));
        actionUploadMessage->setText(QCoreApplication::translate("MainWindow", "Upload message (.BMP)", nullptr));
        actionMethodKutter->setText(QCoreApplication::translate("MainWindow", "Kutter", nullptr));
        actionMethodZhaoKoch->setText(QCoreApplication::translate("MainWindow", "Zhao-Koch", nullptr));
        actionModeInsertion->setText(QCoreApplication::translate("MainWindow", "Insertion", nullptr));
        actionModeExtraction->setText(QCoreApplication::translate("MainWindow", "Extraction", nullptr));
        actionMethodLSBConsecutive->setText(QCoreApplication::translate("MainWindow", "\320\241onsecutive", nullptr));
        actionMethodLSBSeparate->setText(QCoreApplication::translate("MainWindow", "Separate", nullptr));
        actionCipherRSA->setText(QCoreApplication::translate("MainWindow", "RSA", nullptr));
        actionCipherDES->setText(QCoreApplication::translate("MainWindow", "DES", nullptr));
        actionCipherAES->setText(QCoreApplication::translate("MainWindow", "AES", nullptr));
        actionCipherGOST_28147_89->setText(QCoreApplication::translate("MainWindow", "GOST 28147-89", nullptr));
        actionCipherNone->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        actionUploadViewImage->setText(QCoreApplication::translate("MainWindow", "Upload view image (.BMP)", nullptr));
        actionSaveViewImage->setText(QCoreApplication::translate("MainWindow", "Save view image (.BMP)", nullptr));
        labelSep->setText(QCoreApplication::translate("MainWindow", "Container channel \342\206\220 Message channel:", nullptr));
        comboBoxSepContainer1->setItemText(0, QString());
        comboBoxSepContainer1->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxSepContainer1->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxSepContainer1->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelSepArrow1->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        comboBoxSepMessage1->setItemText(0, QString());
        comboBoxSepMessage1->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxSepMessage1->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxSepMessage1->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelSepComma1->setText(QCoreApplication::translate("MainWindow", ",", nullptr));
        comboBoxSepContainer2->setItemText(0, QString());
        comboBoxSepContainer2->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxSepContainer2->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxSepContainer2->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelSepArrow2->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        comboBoxSepMessage2->setItemText(0, QString());
        comboBoxSepMessage2->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxSepMessage2->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxSepMessage2->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelSepComma2->setText(QCoreApplication::translate("MainWindow", ",", nullptr));
        comboBoxSepContainer3->setItemText(0, QString());
        comboBoxSepContainer3->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxSepContainer3->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxSepContainer3->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelSepArrow3->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        comboBoxSepMessage3->setItemText(0, QString());
        comboBoxSepMessage3->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxSepMessage3->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxSepMessage3->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelConContainer->setText(QCoreApplication::translate("MainWindow", "Container bit channel sequence:", nullptr));
        comboBoxConContainer1->setItemText(0, QString());
        comboBoxConContainer1->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxConContainer1->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxConContainer1->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        comboBoxConContainer2->setItemText(0, QString());
        comboBoxConContainer2->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxConContainer2->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxConContainer2->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        comboBoxConContainer3->setItemText(0, QString());
        comboBoxConContainer3->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxConContainer3->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxConContainer3->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelArrow->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        labelConMessage->setText(QCoreApplication::translate("MainWindow", "Message bit channel sequence:", nullptr));
        comboBoxConMessage1->setItemText(0, QString());
        comboBoxConMessage1->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxConMessage1->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxConMessage1->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        comboBoxConMessage2->setItemText(0, QString());
        comboBoxConMessage2->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxConMessage2->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxConMessage2->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        comboBoxConMessage3->setItemText(0, QString());
        comboBoxConMessage3->setItemText(1, QCoreApplication::translate("MainWindow", "R", nullptr));
        comboBoxConMessage3->setItemText(2, QCoreApplication::translate("MainWindow", "G", nullptr));
        comboBoxConMessage3->setItemText(3, QCoreApplication::translate("MainWindow", "B", nullptr));

        labelLSBBits->setText(QCoreApplication::translate("MainWindow", "; Available container bits:", nullptr));
        checkBox7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        checkBox6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        checkBox5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        checkBox4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        checkBox3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        checkBox2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        checkBox1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        checkBox0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelKutter->setText(QCoreApplication::translate("MainWindow", "Kutter", nullptr));
        labelZhaoKoch->setText(QCoreApplication::translate("MainWindow", "Zhao-Koch", nullptr));
        pushButtonInsert->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        pushButtonExtract->setText(QCoreApplication::translate("MainWindow", "Extract", nullptr));
        labelContainer->setText(QString());
        labelMessage->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Message and Container", nullptr));
        labelViewOnePlane->setText(QCoreApplication::translate("MainWindow", "Image bit plane:", nullptr));
        checkBoxView7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        checkBoxView6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        checkBoxView5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        checkBoxView4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        checkBoxView3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        checkBoxView2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        checkBoxView1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        checkBoxView0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelView->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "View", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "Files", nullptr));
        menuMethods->setTitle(QCoreApplication::translate("MainWindow", "Methods", nullptr));
        menuLSB->setTitle(QCoreApplication::translate("MainWindow", "LSB", nullptr));
        menuModes->setTitle(QCoreApplication::translate("MainWindow", "Modes", nullptr));
        menuEncryption->setTitle(QCoreApplication::translate("MainWindow", "Ciphers", nullptr));
        menuAsymmetric->setTitle(QCoreApplication::translate("MainWindow", "Asymmetric", nullptr));
        menuSymmetric->setTitle(QCoreApplication::translate("MainWindow", "Symmetric", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
