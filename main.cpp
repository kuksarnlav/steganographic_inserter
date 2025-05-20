#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/icons/resources/bsu_rfikt.ico"));
	MainWindow w;
	w.show();
	return a.exec();
}
