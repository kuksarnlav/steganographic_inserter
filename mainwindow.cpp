#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

#include <string>
#include <unordered_set>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

	// UI setup
	ui->setupUi(this);
	setWindowTitle("Steganographic tool");

	// Radio button for modes, methods, ciphers
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
	QActionGroup *actionViewGroup = new QActionGroup(this);
	actionViewGroup->setExclusive(true);

	// Label alignments
	ui->labelContainer->setAlignment(Qt::AlignCenter);
	ui->labelMessage->setAlignment(Qt::AlignCenter);

	// Initial interface
	ui->pushButtonExtract->hide();
	ui->pushButtonInsert->show();
	hideLayoutWidgets(ui->hLayoutMethodLSBSep);
	hideLayoutWidgets(ui->hLayoutMethodKutter);
	hideLayoutWidgets(ui->hLayoutMethodZhaoKoch);

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
	} else {
		return false;
	}
}

void MainWindow::on_actionUploadContainer_triggered(){
	// Uploading image
	QString path;
	path = QFileDialog::getOpenFileName(nullptr,
										 "Open container image (.BMP)",
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
	// Uploading image
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

void MainWindow::on_actionModeInsertion_triggered(){
	ui->pushButtonExtract->hide();
	ui->pushButtonInsert->show();

	ui->labelViewOnePlane->hide();
}
void MainWindow::on_actionModeExtraction_triggered(){
	ui->pushButtonInsert->hide();
	ui->pushButtonExtract->show();

	ui->labelViewOnePlane->show();
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

	// Frontend input checking
	if (ui->actionMethodLSBConsecutive->isChecked() || ui->actionMethodLSBSeparate->isChecked()){
		string sequence = ui->comboBoxConContainer1->currentText().toStdString() +
						  ui->comboBoxConContainer2->currentText().toStdString() +
						  ui->comboBoxConContainer3->currentText().toStdString() +
						  ui->comboBoxConMessage1->currentText().toStdString() +
						  ui->comboBoxConMessage2->currentText().toStdString() +
						  ui->comboBoxConMessage3->currentText().toStdString();

		if (sequence.size() != 6){
			qDebug() << "Sequence has " << sequence.size() << " characher(s) instead of 6!\n";
			return;
		}

		// Picture channel sequence must be permutation of 'R','G','B'
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
		if (ui->actionMethodLSBConsecutive->isChecked()){
			if (!isTripletUnique(sequence[0], sequence[1], sequence[2]) ||
				!isTripletUnique(sequence[3], sequence[4], sequence[5])){
				qDebug() << "Wrong insertion sequence: " << sequence << "!\n";
				return;
			}
		} else if (ui->actionMethodLSBSeparate->isChecked()){
			if (!isTripletUnique(sequence[0], sequence[2], sequence[4]) ||
				!isTripletUnique(sequence[1], sequence[3], sequence[5])){
				qDebug() << "Wrong insertion sequence: " << sequence << "!\n";
				return;
			}
		}
	} else if (ui->actionMethodLSBSeparate->isChecked()){

	} else if (ui->actionMethodKutter->isChecked()){

	} else if (ui->actionMethodZhaoKoch->isChecked()){

	}



	//Backend logic
	//...

	//ui->pushButtonUpdate->setEnabled(false);

	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle("Successful insertion");
	msgBox.setText("Insertion was completed successfully.");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}
void MainWindow::on_pushButtonUpdate_clicked(){
	//ui->pushButtonUpdate->setEnabled(false);
}

void MainWindow::on_actionViewAllBitPlanes_triggered(){
	//ui->pushButtonUpdate->setEnabled(true);
	hideLayoutWidgets(ui->hLayoutViewBit);
}
void MainWindow::on_actionViewOneBitPlane_triggered(){
	//ui->pushButtonUpdate->setEnabled(true);

	showLayoutWidgets(ui->hLayoutViewBit);
}
