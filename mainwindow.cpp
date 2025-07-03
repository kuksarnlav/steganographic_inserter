#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

#include "MethodLSB.h"
#include "MethodKutter.h"
#include "MethodZhaoKoch.h"
#include "Viewer.h"
#include "Statistics.h"
#include "types.h"

#include <string>
#include <unordered_set>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

	/// UI setup
	ui->setupUi(this);
	setWindowTitle("Steganographic tool");

	/// Radio button for modes, methods, ciphers
	QActionGroup *actionModesGroup = new QActionGroup(this);
	actionModesGroup->setExclusive(true);
	actionModesGroup->addAction(ui->actionModeInsertion);
	actionModesGroup->addAction(ui->actionModeExtraction);
	QActionGroup *actionMethodsGroup = new QActionGroup(this);
	actionMethodsGroup->setExclusive(true);
	actionMethodsGroup->addAction(ui->actionMethodLSBConsecutive);
	actionMethodsGroup->addAction(ui->actionMethodLSBSeparate);
	actionMethodsGroup->addAction(ui->actionMethodKutter);
	actionMethodsGroup->addAction(ui->actionMethodZhaoKoch);
	QActionGroup *actionCiphersGroup = new QActionGroup(this);
	actionCiphersGroup->setExclusive(true);
	actionCiphersGroup->addAction(ui->actionCipherNone);
	actionCiphersGroup->addAction(ui->actionCipherDES);
	actionCiphersGroup->addAction(ui->actionCipherAES);
	actionCiphersGroup->addAction(ui->actionCipherGOST_28147_89);
	actionCiphersGroup->addAction(ui->actionCipherRSA);

	/// Fiding menues for future implementation
	ui->menuEncryption->menuAction()->setVisible(false);
	ui->menuModes->menuAction()->setVisible(false);

	/// Label alignments
	ui->labelContainer->setAlignment(Qt::AlignCenter);
	ui->labelMessage->setAlignment(Qt::AlignCenter);
	ui->labelStegocontainer->setAlignment(Qt::AlignCenter);
	ui->labelView->setAlignment(Qt::AlignCenter);

	/// Initial interface
	ui->pushButtonInsert->show();
	hideLayoutWidgets(ui->hLayoutMethodLSBSep);
	hideLayoutWidgets(ui->hLayoutMethodKutter);
	hideLayoutWidgets(ui->hLayoutMethodZhaoKoch);

	/// Pixmap size correction
	connect(ui->tabWidget, &QTabWidget::currentChanged, this, [this](int index){
		if (index == 0){
			QPixmap pixmap(pathContainer);
			ui->labelContainer->setPixmap(pixmap.scaled(ui->labelContainer->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
			QPixmap pixmap2(pathMessage);
			ui->labelMessage->setPixmap(pixmap2.scaled(ui->labelMessage->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
		}
		if (index == 1){
			QPixmap pixmapStegocontainer(pathStegocontainer);
			ui->labelStegocontainer->setPixmap(pixmapStegocontainer.scaled(ui->labelStegocontainer->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
		}
		if (index == 2){
			QPixmap pixmapView(pathView);
			ui->labelView->setPixmap(pixmapView.scaled(ui->labelView->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
		}
	});

	showMaximized();
}
MainWindow::~MainWindow(){
	delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event){
	if (pathContainer != ""){
		QPixmap pixmap(pathContainer);
		ui->labelContainer->setPixmap(pixmap.scaled(ui->labelContainer->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
	if (pathMessage != ""){
		QPixmap pixmap(pathMessage);
		ui->labelMessage->setPixmap(pixmap.scaled(ui->labelMessage->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
	QMainWindow::resizeEvent(event);
}


void MainWindow::hideLayoutWidgets(QHBoxLayout* l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->hide();
	}
}
void MainWindow::hideLayoutWidgets(QVBoxLayout* l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->hide();
	}
}
void MainWindow::showLayoutWidgets(QHBoxLayout* l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->show();
	}
}
void MainWindow::showLayoutWidgets(QVBoxLayout* l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->show();
	}
}

void MainWindow::enableLayoutWidgets(QHBoxLayout *l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->setEnabled(true);
	}
}
void MainWindow::enableLayoutWidgets(QVBoxLayout *l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->setEnabled(true);
	}
}
void MainWindow::disableLayoutWidgets(QHBoxLayout *l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->setEnabled(false);
	}
}
void MainWindow::disableLayoutWidgets(QVBoxLayout *l){
	for (int i = 0; i < l->count(); i++){
		QWidget* widget = l->itemAt(i)->widget();
		if (widget) widget->setEnabled(false);
	}
}


bool MainWindow::canShowInsertButton(){
	if (pathContainer != "" && pathMessage != ""){
		return true;
	}
	return false;
}
bool MainWindow::canShowViewButton()
{
	if (pathView != ""){
		return true;
	}
	return false;
}

void MainWindow::on_actionUploadContainer_triggered(){
	/// Uploading image
	QString path;
	path = QFileDialog::getOpenFileName(nullptr,
										 "Open container image (.BMP)",
										 "C:/",
										 "Media files (*.bmp)");

	/// Function for non ASCII strokes detection
	auto isStrokeASCII = [](const QString &s){
		for (const QChar &c : s){
			if (c.unicode() > 127){
				return false;
			}
		}
		return true;
	};
	if (path != ""){
		pathContainer = path;
		if (!isStrokeASCII(pathContainer)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Non ASCII characters in the path aren't supported!");
			QString errorInfo = "Problem path:\n" + pathContainer;
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		QPixmap pixmapContainer(pathContainer);
		ui->labelContainer->setPixmap(pixmapContainer.scaled(ui->labelContainer->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}

	if (canShowInsertButton()){
		ui->pushButtonInsert->setEnabled(true);
	}
}
void MainWindow::on_actionUploadMessage_triggered(){
	/// Uploading image
	QString path;
	path = QFileDialog::getOpenFileName(nullptr,
										 "Open message image (.BMP)",
										 "C:/",
										 "Media files (*.bmp)");
	auto isStrokeASCII = [](const QString &s){
		for (const QChar &c : s){
			if (c.unicode() > 127){
				return false;
			}
		}
		return true;
	};
	if (path != ""){
		pathMessage = path;
		if (!isStrokeASCII(pathMessage)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Non ASCII characters in the path aren't supported!");
			QString errorInfo = "Problem path:\n" + pathMessage;
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		QPixmap pixmapContainer(pathMessage);
		ui->labelMessage->setPixmap(pixmapContainer.scaled(ui->labelMessage->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}

	if (canShowInsertButton()){
		ui->pushButtonInsert->setEnabled(true);
	}
}

void MainWindow::on_actionUploadViewImage_triggered()
{
	/// Uploading image
	QString path;
	path = QFileDialog::getOpenFileName(nullptr,
										"Open message image (.BMP)",
										"C:/",
										"Media files (*.bmp)");
	auto isStrokeASCII = [](const QString &s){
		for (const QChar &c : s){
			if (c.unicode() > 127){
				return false;
			}
		}
		return true;
	};
	if (path != ""){
		pathView = path;
		if (!isStrokeASCII(pathView)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Non ASCII characters in the path aren't supported!");
			QString errorInfo = "Problem path:\n" + pathView;
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		QPixmap pixmapView(pathView);
		ui->labelView->setPixmap(pixmapView.scaled(ui->labelView->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}

	if (canShowViewButton()){
		ui->pushButtonView->setEnabled(true);
	}
}

void MainWindow::on_actionMethodLSBConsecutive_triggered(){
	hideLayoutWidgets(ui->hLayoutMethodKutter);
	hideLayoutWidgets(ui->hLayoutMethodZhaoKoch);
	hideLayoutWidgets(ui->hLayoutMethodLSBSep);

	showLayoutWidgets(ui->hLayoutMethodLSBCon);
	showLayoutWidgets(ui->hLayoutMethodLSBBits);
}
void MainWindow::on_actionMethodLSBSeparate_triggered(){
	hideLayoutWidgets(ui->hLayoutMethodKutter);
	hideLayoutWidgets(ui->hLayoutMethodZhaoKoch);
	hideLayoutWidgets(ui->hLayoutMethodLSBCon);

	showLayoutWidgets(ui->hLayoutMethodLSBSep);
	showLayoutWidgets(ui->hLayoutMethodLSBBits);
}
void MainWindow::on_actionMethodKutter_triggered(){
	hideLayoutWidgets(ui->hLayoutMethodLSBCon);
	hideLayoutWidgets(ui->hLayoutMethodLSBSep);
	hideLayoutWidgets(ui->hLayoutMethodLSBBits);
	hideLayoutWidgets(ui->hLayoutMethodZhaoKoch);

	showLayoutWidgets(ui->hLayoutMethodKutter);
}
void MainWindow::on_actionMethodZhaoKoch_triggered(){
	hideLayoutWidgets(ui->hLayoutMethodLSBCon);
	hideLayoutWidgets(ui->hLayoutMethodLSBSep);
	hideLayoutWidgets(ui->hLayoutMethodLSBBits);
	hideLayoutWidgets(ui->hLayoutMethodKutter);

	showLayoutWidgets(ui->hLayoutMethodZhaoKoch);
}

void MainWindow::on_pushButtonInsert_clicked(){
	/// Frontend input checking
	if (ui->actionMethodLSBConsecutive->isChecked() || ui->actionMethodLSBSeparate->isChecked()){
		string sequence = ui->comboBoxConContainer1->currentText().toStdString() +
						  ui->comboBoxConContainer2->currentText().toStdString() +
						  ui->comboBoxConContainer3->currentText().toStdString() +
						  ui->comboBoxConMessage1->currentText().toStdString() +
						  ui->comboBoxConMessage2->currentText().toStdString() +
						  ui->comboBoxConMessage3->currentText().toStdString();

		if (sequence.size() != 6){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Sequence has " + QString::number(sequence.size()) + " characher(s) instead of 6!");
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}

		/// Picture channel sequence must be permutation of 'R','G','B'
		auto isTripletUnique = [](char c1, char c2, char c3) -> bool{
			unordered_set<char> set;
			set.insert(c1);
			set.insert(c2);
			set.insert(c3);
			if (set.count('R') != 1 ||
				set.count('G') != 1 ||
				set.count('B') != 1) return false;
			return true;
		};

		/// Wrong channel sequence processing
		if (ui->actionMethodLSBConsecutive->isChecked()){
			if (!isTripletUnique(sequence[0], sequence[1], sequence[2]) ||
				!isTripletUnique(sequence[3], sequence[4], sequence[5])){
				QMessageBox errorMessageBox;
				errorMessageBox.setText("Wrong insertion sequence: " + QString::fromStdString(sequence) + "!");
				errorMessageBox.setIcon(QMessageBox::Critical);
				errorMessageBox.exec();
				return;
			}
		} else if (ui->actionMethodLSBSeparate->isChecked()){
			if (!isTripletUnique(sequence[0], sequence[2], sequence[4]) ||
				!isTripletUnique(sequence[1], sequence[3], sequence[5])){
				QMessageBox errorMessageBox;
				errorMessageBox.setText("Wrong insertion sequence: " + QString::fromStdString(sequence) + "!");
				errorMessageBox.setIcon(QMessageBox::Critical);
				errorMessageBox.exec();
				return;
			}
		}

		/// Shared LSB inputs
		unsigned char inputBitsCheckedContainer = 0b0000'0000;
		if (ui->checkBox0->isChecked()) inputBitsCheckedContainer |= 0b0000'0001;
		if (ui->checkBox1->isChecked()) inputBitsCheckedContainer |= 0b0000'0010;
		if (ui->checkBox2->isChecked()) inputBitsCheckedContainer |= 0b0000'0100;
		if (ui->checkBox3->isChecked()) inputBitsCheckedContainer |= 0b0000'1000;
		if (ui->checkBox4->isChecked()) inputBitsCheckedContainer |= 0b0001'0000;
		if (ui->checkBox5->isChecked()) inputBitsCheckedContainer |= 0b0010'0000;
		if (ui->checkBox6->isChecked()) inputBitsCheckedContainer |= 0b0100'0000;
		if (ui->checkBox7->isChecked()) inputBitsCheckedContainer |= 0b1000'0000;
		string inputPathContainer = pathContainer.toStdString(),
			inputPathMessage = pathMessage.toStdString(),
			inputPathDir = QDir::currentPath().toStdString() + "/",
			inputInsertionSequence;
		/// Container capacity must be >= message weight
		if (MethodLSB::getContainerCapacity(inputPathContainer, inputBitsCheckedContainer) < MethodLSB::getMessageWeight(inputPathMessage)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Container capacity is lower than message weight!");
			QString errorInfo = "Container capacity: " + QString::number(MethodLSB::getContainerCapacity(inputPathContainer, inputBitsCheckedContainer)) + " bit(s)"
								"\nMessage weight: " + QString::number(MethodLSB::getMessageWeight(inputPathMessage)) + " bit(s)";
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		MethodLSB methodLSB;
		/// Choosing right LSB type
		if (ui->actionMethodLSBConsecutive->isChecked()){
			LSBType inputLSBType = Consecutive;
			inputInsertionSequence += ui->comboBoxConContainer1->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxConContainer2->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxConContainer3->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxConMessage1->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxConMessage2->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxConMessage3->currentText().toStdString();
			methodLSB.insertMessage(inputPathContainer,
									inputPathMessage,
									inputPathDir,
									inputLSBType,
									inputInsertionSequence,
									inputBitsCheckedContainer);
		} else if (ui->actionMethodLSBSeparate->isChecked()){
			LSBType inputLSBType = Separate;
			inputInsertionSequence += ui->comboBoxSepContainer1->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxSepMessage1->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxSepContainer2->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxSepMessage2->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxSepContainer3->currentText().toStdString();
			inputInsertionSequence += ui->comboBoxSepMessage3->currentText().toStdString();
			methodLSB.insertMessage(inputPathContainer,
									inputPathMessage,
									inputPathDir,
									inputLSBType,
									inputInsertionSequence,
									inputBitsCheckedContainer);
		}
	} else if (ui->actionMethodKutter->isChecked()){
		string inputPathContainer = pathContainer.toStdString(),
			inputPathMessage = pathMessage.toStdString(),
			inputPathDir = QDir::currentPath().toStdString() + "/",
			inputMessageSequence,
			inputContainerSequence;
		inputMessageSequence += ui->comboBoxKutterMessageChannel1->currentText().toStdString();
		inputMessageSequence += ui->comboBoxKutterMessageChannel2->currentText().toStdString();
		inputMessageSequence += ui->comboBoxKutterMessageChannel3->currentText().toStdString();
		inputContainerSequence += ui->comboBoxKutterContainerChannel1->currentText().toStdString();
		inputContainerSequence += ui->comboBoxKutterContainerChannel2->currentText().toStdString();
		inputContainerSequence += ui->comboBoxKutterContainerChannel3->currentText().toStdString();
		double input_insertion_power = ui->doubleSpinBoxKutterInsertionPower->value();
		if (inputMessageSequence[0] == inputMessageSequence[1] || inputMessageSequence[0] == inputMessageSequence[2]){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Message sequence should be a permutation of \"RGB\"!");
			QString errorInfo = "Problem sequence:\n" + QString::fromStdString(inputMessageSequence);
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		if (inputContainerSequence[0] == inputContainerSequence[1] || inputContainerSequence[0] == inputContainerSequence[2]){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Container sequence should be a permutation of \"RGB\"!");
			QString errorInfo = "Problem sequence:\n" + QString::fromStdString(inputContainerSequence);
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		/// Container capacity must be >= message weight
		if (MethodKutter::getContainerCapacity(inputPathContainer) < MethodKutter::getMessageWeight(inputPathMessage)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Container capacity is lower than message weight!");
			QString errorInfo = "Container capacity: " + QString::number(MethodKutter::getContainerCapacity(inputPathContainer)) + " bit(s)"
								"\nMessage weight: " + QString::number(MethodKutter::getMessageWeight(inputPathMessage)) + " bit(s)";
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		MethodKutter methodKutter;
		methodKutter.insertMessage(inputPathContainer,
								   inputPathMessage,
								   inputPathDir,
								   input_insertion_power,
								   inputMessageSequence,
								   inputContainerSequence);
	} else if (ui->actionMethodZhaoKoch->isChecked()){
		string inputPathContainer = pathContainer.toStdString(),
			inputPathMessage = pathMessage.toStdString(),
			inputPathDir = QDir::currentPath().toStdString() + "/",
			inputMessageSequence,
			inputContainerSequence;
		double inputThreshold;
		inputMessageSequence += ui->comboBoxZhaoMessageChannel1->currentText().toStdString();
		inputMessageSequence += ui->comboBoxZhaoMessageChannel2->currentText().toStdString();
		inputMessageSequence += ui->comboBoxZhaoMessageChannel3->currentText().toStdString();
		inputContainerSequence += ui->comboBoxZhaoContainerChannel1->currentText().toStdString();
		inputContainerSequence += ui->comboBoxZhaoContainerChannel2->currentText().toStdString();
		inputContainerSequence += ui->comboBoxZhaoContainerChannel3->currentText().toStdString();
		if (inputMessageSequence[0] == inputMessageSequence[1] || inputMessageSequence[0] == inputMessageSequence[2]){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Message sequence should be a permutation of \"RGB\"!");
			QString errorInfo = "Problem sequence:\n" + QString::fromStdString(inputMessageSequence);
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		if (inputContainerSequence[0] == inputContainerSequence[1] || inputContainerSequence[0] == inputContainerSequence[2]){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Message sequence should be a permutation of \"RGB\"!");
			QString errorInfo = "Problem sequence:\n" + QString::fromStdString(inputContainerSequence);
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		inputThreshold = static_cast<double>(ui->spinBoxZhaoThreshold->value());
		/// Container capacity must be >= message weight
		if (MethodZhaoKoch::getContainerCapacity(inputPathContainer) < MethodZhaoKoch::getMessageWeight(inputPathMessage)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Container capacity is lower than message weight!");
			QString errorInfo = "Container capacity: " + QString::number(MethodZhaoKoch::getContainerCapacity(inputPathContainer)) + " bit(s)"
								"\nMessage weight: " + QString::number(MethodZhaoKoch::getMessageWeight(inputPathMessage)) + " bit(s)";
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
		MethodZhaoKoch methodZhaoKoch;
		int inputCoef1X = ui->spinBoxZhao1stCoefX->value(),
			inputCoef1Y = ui->spinBoxZhao1stCoefY->value(),
			inputCoef2X = ui->spinBoxZhao2ndCoefX->value(),
			inputCoef2Y = ui->spinBoxZhao2ndCoefY->value();
		methodZhaoKoch.insertMessage(inputPathContainer,
									 inputPathMessage,
									 inputPathDir,
									 inputMessageSequence,
									 inputContainerSequence,
									 inputThreshold,
									 inputCoef1X,
									 inputCoef1Y,
									 inputCoef2X,
									 inputCoef2Y);
	}

	/// Function for checking valid paths
	auto isStrokeASCII = [](const QString &s){
		for (const QChar &c : s){
			if (c.unicode() > 127){
				return false;
			}
		}
		return true;
	};

	Method method;
	QString nameStegocontainer = QString::fromStdString(method.getNameStegocontainer());
	QString path = QDir::currentPath() + "/" + nameStegocontainer;
	if (path != ""){
		pathStegocontainer = path;
		pathView = path;
		ui->pushButtonView->setEnabled(true);
		if (!isStrokeASCII(pathStegocontainer)){
			QMessageBox errorMessageBox;
			errorMessageBox.setText("Non ASCII characters in the path aren't supported!");
			QString errorInfo = "Problem path:\n" + pathStegocontainer;
			errorMessageBox.setInformativeText(errorInfo);
			errorMessageBox.setIcon(QMessageBox::Critical);
			errorMessageBox.exec();
			return;
		}
	}

	Statistics statistics;
	statistics.calculateStatistics(pathContainer.toStdString(),
								   pathMessage.toStdString(),
								   pathStegocontainer.toStdString());
	ui->labelContainerBit1PercentageValue->setText(QString::fromStdString(statistics.getContainerBit1Percentage()));
	ui->labelMessageBit1PercentageValue->setText(QString::fromStdString(statistics.getMessageBit1Percentage()));
	ui->labelStegocontainerBit1PercentageValue->setText(QString::fromStdString(statistics.getStegocontainerBit1Percentage()));
	ui->labelChangedBitsQuantityValue->setText(QString::fromStdString(statistics.getStegocontainerChangedBitsPercentage()));

	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle("Successful insertion");
	msgBox.setText("Insertion was completed successfully.");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

void MainWindow::on_pushButtonView_clicked()
{
	Viewer viewer;
	string pathExport = QDir::currentPath().toStdString() + "/"; /// export path
	string pathToImage = pathView.toStdString(); /// image for viewing path
	vector<int> viewBits; /// checked bit planes
	if (ui->checkBoxView7->isChecked()) viewBits.push_back(7);
	if (ui->checkBoxView6->isChecked()) viewBits.push_back(6);
	if (ui->checkBoxView5->isChecked()) viewBits.push_back(5);
	if (ui->checkBoxView4->isChecked()) viewBits.push_back(4);
	if (ui->checkBoxView3->isChecked()) viewBits.push_back(3);
	if (ui->checkBoxView2->isChecked()) viewBits.push_back(2);
	if (ui->checkBoxView1->isChecked()) viewBits.push_back(1);
	if (ui->checkBoxView0->isChecked()) viewBits.push_back(0);

	string viewChannels;
	if (ui->checkBoxViewR->isChecked()) viewChannels += "R";
	if (ui->checkBoxViewG->isChecked()) viewChannels += "G";
	if (ui->checkBoxViewB->isChecked()) viewChannels += "B";
	viewer.createView(viewBits, pathToImage, pathExport, viewChannels);

	QPixmap pixmapView(QString::fromStdString(viewer.getPathViewedImage()));
	ui->labelView->setPixmap(pixmapView.scaled(ui->labelView->size(), Qt::KeepAspectRatio, Qt::FastTransformation));

	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle("Successful view transformation");
	msgBox.setText("View transformation was completed successfully.");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

