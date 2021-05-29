#include <QtDebug>

#include <QDir>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QPalette>
#include <QTextStream>
#include <QCoreApplication>

#include "MainWindow.hpp"
#include "Ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    m_btnStyle = QString(" QPushButton::flat"
                                "{"
                                    "border:none;"
                                "}" 
                                "QPushButton"
                                "{"
                                    "text-align:left;"
                                    "font-size:25px;"
                                    "color:white;"
                                "}"
                                "QPushButton::focus"
                                "{"
                                    "background-color:rgb(0, 255, 141);"
                                    "color:black;"
                                "}"
                                );

    m_abs_path = QDir::homePath();

    ui->setupUi(this);
    posLenForPath(ui->path, m_abs_path);;

    QFileInfoList* list = DirContent(QString(QDir::homePath()));

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);

    for(int i = 1; i < list->size(); ++i)
    {
        QPushButton* button = new QPushButton(' ' + (list->at(i)).fileName(), ui->scrollAreaWidgetContents);
        button->setFixedSize(305, 40);
        button->setFlat(true);
        button->setStyleSheet(m_btnStyle);

        button->installEventFilter(this);

        connect(button, &QPushButton::clicked, this, &MainWindow::changeDir);

        m_flist.append(button);

        vbox->addWidget(button);
    }

    ui->scrollAreaWidgetContents->setLayout(vbox);

    setAutoFillBackground(true);

    quitDg = new QuitDialog(this);
}

MainWindow::~MainWindow()
{ 
    delete quitDg;
    delete ui;
}

void MainWindow::posLenForPath(QLabel* path, const QString& new_path)
{
    /*40 is the minimum position for the path
     *290 is the maximum
     *
     *40 is the fixed position of y for the path
     *31 is the fixed height of the path
     *22 is the maximum length of the path string
     */

    int width = new_path.length() * 12 + 4;
    int x = (40 + (290 / 2)) - (width / 2);

    //If the length of the path is more than 290
    //then only the rest of it is displayed in the label 
    if(width > 290)
    {
        path->setGeometry(40, 40, 290, 31);

        QString short_path = new_path.right(24 - 2);
        int index = short_path.indexOf('/');
        short_path = short_path.mid(index, 22);
        path->setText(".." + short_path);
    }
    //otherwise, the length is set according to the length
    //of the path string
    else
    {
        path->setGeometry(x, 40, width, 31);
        path->setText(new_path);
    }

}

Ui::MainWindow* MainWindow::getUi() { return ui; }
QuitDialog* MainWindow::getQuitDialog() { return quitDg; }
QVector<QPushButton*> MainWindow::getButtonList() { return m_flist; }
QFileInfoList* MainWindow::getListOfDir() { return m_list; }

//Gets all dirs and files as a QFileInfoList (along a given path)
//
QFileInfoList* MainWindow::DirContent(const QString& path)
{
    QDir* dir = new QDir(path);

    dir->setFilter(QDir::Files | QDir::AllDirs | QDir::Hidden);
    dir->setSorting(QDir::Name);

    return new QFileInfoList(dir->entryInfoList());
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    //If the Q key is pressed, a window appears to
    //quit the application
    if(e->key() == Qt::Key_Q)
        quitDg->show();
    //'End' key sets the focus on the last button
    else if(e->key() == Qt::Key_End)
    {
        m_flist.last()->setFocus();
        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
    }
    //'Home' key sets the focus on the first button
    else if(e->key() == Qt::Key_Home)
    {
        m_flist.first()->setFocus();
        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->minimum());
    }
}

void MainWindow::closeEvent(QCloseEvent* e) 
{
    Q_UNUSED(e);
    QCoreApplication::exit(0);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	int index;

	if((index = m_flist.indexOf((QPushButton*)obj)) != -1)
	{
		if(event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = (QKeyEvent*) event;

			if(keyEvent->key() == Qt::Key_Return)
			{
				cd(m_flist[index]);
				return true;
			}
			else
				return false;

		}
		else
			return false;
	}
	else
		return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setDirContent(const QString& cdpath)
{
    QDir* dir = new QDir(m_abs_path);

    dir->cd(cdpath);

    m_abs_path = dir->absolutePath();

    posLenForPath(ui->path, m_abs_path);

    QFileInfoList* list = DirContent(m_abs_path);

    m_flist.clear();
    clearLayout();

    QVBoxLayout* vbox = (QVBoxLayout*) ui->scrollAreaWidgetContents->layout();

    for(int i = 1; i < list->size(); ++i)
    {
        QPushButton* button = new QPushButton(' ' + (list->at(i)).fileName(), ui->scrollAreaWidgetContents);
        button->setFixedSize(305, 40);
        button->setFlat(true);
        button->setStyleSheet(m_btnStyle);

        button->installEventFilter(this);

        connect(button, &QPushButton::clicked, this, &MainWindow::changeDir);

        m_flist.append(button);

        vbox->addWidget(button);
    }

    m_flist.first()->setFocus();
}

void MainWindow::changeDir()
{
    QPushButton* snd = (QPushButton*) QObject::sender();

    // //It is necessary to remove the first
    // //character, since it is a space
    // QString cd = snd->text();
    // cd.remove(0, 1);

    // setDirContent(cd);

    cd(snd);

}

void MainWindow::clearLayout()
{
    QLayout* layout = ui->scrollAreaWidgetContents->layout();

    if(layout)
    {
        QLayoutItem* item;
        while((item = layout->takeAt(0)))
        {
            delete item->widget();
            delete item;
        }
    }
}

void MainWindow::cd(QPushButton* button)
{
	//It is necessary to remove the first
    //character, since it is a space
	QString cd = button->text();
	cd.remove(0, 1);

	setDirContent(cd);
}