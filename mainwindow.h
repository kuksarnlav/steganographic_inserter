#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
	Q_OBJECT

public:

	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:

	void on_actionUploadContainer_triggered();
	void on_actionUploadMessage_triggered();
	void on_actionMethodLSBConsecutive_triggered();
	void on_actionMethodLSBSeparate_triggered();
	void on_actionMethodKutter_triggered();
	void on_actionMethodZhaoKoch_triggered();

	void on_pushButtonInsert_clicked();
	void on_actionUploadViewImage_triggered();

	void on_pushButtonView_clicked();

private:
	Ui::MainWindow *ui;

protected:

	void resizeEvent(QResizeEvent *event);

	void hideLayoutWidgets(QHBoxLayout* l);
	void hideLayoutWidgets(QVBoxLayout* l);
	void showLayoutWidgets(QHBoxLayout* l);
	void showLayoutWidgets(QVBoxLayout* l);

	void enableLayoutWidgets(QHBoxLayout* l);
	void enableLayoutWidgets(QVBoxLayout* l);
	void disableLayoutWidgets(QHBoxLayout* l);
	void disableLayoutWidgets(QVBoxLayout* l);

	bool canShowInsertButton();
	bool canShowViewButton();

	QString pathContainer;
	QString pathMessage;
	QString pathStegocontainer;
	QString pathView;
};
#endif // MAINWINDOW_H
