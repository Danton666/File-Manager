#ifndef __TEST_MAIN_WINDOW_HPP__
#define __TEST_MAIN_WINDOW_HPP__

#include <QMainWindow>

class Test_MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit Test_MainWindow(QWidget* parent = nullptr);
	~Test_MainWindow();

private slots:
	/*Test quit dialog*/
	void quitDialog();
	void closeAppAfterClickYes();
	void closeDialogAfterClickNo();

	/*Pressing 'Home' and 'End'*/
	void pressHomeAndEnd();

};

#endif //__TEST_MAIN_WINDOW_HPP__