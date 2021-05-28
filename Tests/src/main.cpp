#include <QTest>
#include <QApplication>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "tests/frontend/test_MainWindow.hpp"

#include "MainWindow.hpp"
#include "Dialogs/QuitDialog.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	freopen("testfront.log", "w", stdout);
	QApplication app(argc, argv);

	QTest::qExec(new Test_MainWindow, argc, argv);

	return 0;
}