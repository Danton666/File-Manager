#include <QDir>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QPalette>
#include <QTextStream>
#include <QCoreApplication>

#include "MainWindow.hpp"
#include "Ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->path->setText(QDir::homePath());

    QFileInfoList* list = DirContent(QString(QDir::homePath()));

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);

    for(int i = 0; i < list->size(); ++i)
    {
        QPushButton* button = new QPushButton(' ' + (list->at(i)).fileName());
        button->setFixedSize(305, 40);
        button->setFlat(true);
        button->setStyleSheet("QPushButton::flat{border:none;} QPushButton{text-align:left; font-size:25px; color:white;} QPushButton::focus{background-color:rgb(0, 255, 141); color:black;}");

        m_flist.append(button);

        vbox->addWidget(button);
    }

    ui->scrollAreaWidgetContents->setLayout(vbox);

    setAutoFillBackground(true);

    quitDg = new QuitDialog(this);
}

MainWindow::~MainWindow()
{ 
    delete ui;
    ui = nullptr;

    delete quitDg;
    quitDg = nullptr;
}

Ui::MainWindow* MainWindow::getUi() { return ui; }
QuitDialog* MainWindow::getQuitDialog() { return quitDg; }
QVector<QPushButton*> MainWindow::getButtonList() { return m_flist; }
QFileInfoList* MainWindow::getListOfDir() { return m_list; }


QFileInfoList* MainWindow::DirContent(const QString& path)
{
    QDir* dir = new QDir(path);

    dir->setFilter(QDir::Files | QDir::AllDirs | QDir::Hidden);
    dir->setSorting(QDir::Name);

    return new QFileInfoList(dir->entryInfoList());
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Q)
        quitDg->show();
    else if(e->key() == Qt::Key_Up && m_flist[0]->hasFocus())
        m_flist[0]->setFocus();
    else if(e->key() == Qt::Key_Down && m_flist[m_flist.size() - 1]->hasFocus())
        m_flist[m_flist.size() - 1]->setFocus();
}

void MainWindow::closeEvent(QCloseEvent* e) 
{
    Q_UNUSED(e);
    QCoreApplication::exit(0); 
}

void MainWindow::focusInEvent(QFocusEvent* e)
{
    Q_UNUSED(e);

    m_flist[0]->setFocus();

    if(!focusNextChild())
        m_flist[m_flist.size() - 1]->setFocus();
    else if(!focusPreviousChild())
        m_flist[0]->setFocus();
}