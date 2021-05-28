#include <QTest>
#include <QTimer>
#include <QApplication>
#include <QCoreApplication>

#include <iostream>

#include "tests/frontend/test_MainWindow.hpp"

#include "MainWindow.hpp"
#include "Dialogs/QuitDialog.hpp"

Test_MainWindow::Test_MainWindow(QWidget* parent) : QMainWindow(parent)
{
}

Test_MainWindow::~Test_MainWindow()
{
}

void Test_MainWindow::quitDialog()
{
	MainWindow* window = new MainWindow;
	window->show();

	QTest::keyClick(window, Qt::Key_Q);

	QVERIFY(window->getQuitDialog()->isVisible()); //true

	delete window;
	window = nullptr;
}

void Test_MainWindow::closeAppAfterClickYes()
{
	MainWindow* window = new MainWindow;
	window->show();

	QTest::keyClick(window, Qt::Key_Q);
	QVERIFY(window->getQuitDialog()->isVisible());

	QTest::keyClick(window->getQuitDialog()->getYes(), Qt::Key_Enter);

	QVERIFY(!window->isVisible()); //false
	QVERIFY(!window->getQuitDialog()->isVisible()); //false

	delete window;
	window = nullptr;
}

void Test_MainWindow::closeDialogAfterClickNo()
{
	MainWindow* window = new MainWindow;
	window->show();

	QTest::keyClick(window, Qt::Key_Q);
	QVERIFY(window->getQuitDialog()->isVisible());

	QTest::keyClick(window->getQuitDialog()->getNo(), Qt::Key_Enter);

	QVERIFY(!window->getQuitDialog()->isVisible()); //false
	QVERIFY(window->isVisible()); //true

	delete window;
	window = nullptr;
}