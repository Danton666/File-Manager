#include <QtDebug>

#include <QDir>
#include <QRect>
#include <QDateTime>
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

    //Hot keys
    ctrl_i = false;

    m_btnStyle = QString(" QPushButton::flat"
                                "{"
                                    "border:none;"
                                "}" 
                                "QPushButton"
                                "{"
                                    "text-align:left;"
                                    "font-size:25px;"
                                "}"
                                "QPushButton::focus"
                                "{"
                                    "background-color:rgb(0, 255, 141);"
                                    "color:black;"
                                "}"
                                );

    m_abs_path = QDir::homePath();

    ui->setupUi(this);
    posLenForPath(ui->path, m_abs_path);

    QVBoxLayout* vbox = new QVBoxLayout;
    // vbox->setObjectName("vbox");
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);

    ui->scrollAreaWidgetContents->setLayout(vbox);

    setDirContent(".", vbox);
    setAutoFillBackground(true);

    current_btn = m_flist.first();

    quitDg = new QuitDialog(this);
    mkdirDg = new MkdirDialog(this);
    delDg = new DeleteDialog(this);
    crtfDg = new CrtFileDialog(this);
    cpDg = new CopyDialog(this);
}

MainWindow::~MainWindow()
{ 
    delete quitDg;
    delete mkdirDg;
    delete delDg;
    delete crtfDg;

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

    dir->setFilter(QDir::Files | QDir::AllDirs | QDir::Hidden | QDir::NoDot);
    dir->setSorting(QDir::Name);

    return new QFileInfoList(dir->entryInfoList());
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    //If the Q key is pressed, a window appears to
    //quit the application
    if(e->key() == Qt::Key_F10)
        quitDg->exec();
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
    else if(e->key() == Qt::Key_F7)
    {
        mkdirDg->exec();
        setDirContent(".", (QVBoxLayout*) ui->scrollAreaWidgetContents->layout());
    }
    else if(e->key() == Qt::Key_F6)
    {
        delDg->exec();
        setDirContent(".", (QVBoxLayout*) ui->scrollAreaWidgetContents->layout());
    }
    else if(e->key() == Qt::Key_F3)
    {
        crtfDg->exec();
        setDirContent(".", (QVBoxLayout*) ui->scrollAreaWidgetContents->layout());
    }
    else if(e->key() == Qt::Key_F4)
    {
        cpDg->exec();
        setDirContent(".", (QVBoxLayout*) ui->scrollAreaWidgetContents->layout());   
    }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    int index;

    if((index = m_flist.indexOf((QPushButton*)obj)) != -1)
    {
        if(current_btn != (QPushButton*)obj)
        {
            current_btn = (QPushButton*)obj;

            if(ctrl_i)
                setInfo((QPushButton*)obj);
        }

        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = (QKeyEvent*) event;

            if(keyEvent->key() == Qt::Key_Return)
            {
                cd(m_flist[index]);
                return true;
            }
            else if(keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_I)
            {
                if(!ctrl_i)
                {
                    setInfo((QPushButton*)obj);
                    ctrl_i = true;

                    return true;
                }
                else
                {
                    clearInfo();
                    ctrl_i = false;

                    return true;
                }

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

void MainWindow::setDirContent(const QString& cdpath, QVBoxLayout* vbox)
{
    QDir* dir = new QDir(m_abs_path);

    dir->cd(cdpath);

    m_abs_path = dir->absolutePath();

    posLenForPath(ui->path, m_abs_path);

    QFileInfoList* list = DirContent(m_abs_path);

    m_flist.clear();
    clearLayout();

    // QVBoxLayout* vbox = (QVBoxLayout*) ui->scrollAreaWidgetContents->layout();

    //So that there are no spaces
    //between the buttons if there are less that 17
    // of them
    if(list->size() < 17)
        ui->scrollArea->setGeometry(QRect(33, 64, 307, list->size() * 42));
    else
        ui->scrollArea->setGeometry(QRect(33, 64, 307, 691));

    for(int i = 0; i < list->size(); ++i)
    {
        QPushButton* button = new QPushButton(' ' + (list->at(i)).fileName(), ui->scrollAreaWidgetContents);
        button->setFixedSize(305, 40);
        button->setFlat(true);
        button->setStyleSheet(m_btnStyle);

        if(list->at(i).isDir())
            button->setStyleSheet(m_btnStyle + " QPushButton{color:white;}");
        else if(list->at(i).isHidden())
            button->setStyleSheet(m_btnStyle + " QPushButton{color:grey;}");
        else if(list->at(i).isExecutable())
            button->setStyleSheet(m_btnStyle + " QPushButton{color:green;}");
        else
            button->setStyleSheet(m_btnStyle + " QPushButton{color:rgb(135, 99, 99);}");

        button->installEventFilter(this);

        connect(button, &QPushButton::clicked, this, &MainWindow::changeDir);

        m_flist.append(button);

        vbox->addWidget(button);
    }

    m_flist.first()->setFocus();

    delete dir;
}

//It can be used only as a slot
//it uses QObject::sender
void MainWindow::changeDir()
{
    QPushButton* snd = (QPushButton*) QObject::sender();
    cd(snd);
}

//Removes all widgets of the scrollAreaWidgetContents' layout
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

//Change directory
void MainWindow::cd(const QPushButton* button)
{
    //It is necessary to remove the first
    //character, since it is a space
    QString cd = button->text();
    cd.remove(0, 1);

    setDirContent(cd, (QVBoxLayout*) ui->scrollAreaWidgetContents->layout());
}

void MainWindow::setInfo(const QPushButton* button)
{
    QFileInfo* info = new QFileInfo(m_abs_path + '/' + button->text().remove(0, 1));

    if(info)
    {
        //File type
        if(info->isDir())
            m_type = "directory";
        else if(info->isHidden())
            m_type = "hidden";
        else if(info->isFile())
            m_type = "file";
        else
            m_type = "unknown";

        //Size
        m_size = info->size();

        //Birth time
        m_birth_time = info->birthTime().toString();

        //is it a symbol link
        if(info->isSymLink())
            m_symbol_link = "Yes";
        else
            m_symbol_link = "No";

        //Last modified
        m_last_modified = info->lastModified().toString();

        //Last read
        m_last_read = info->lastRead().toString();

        //Owner
        m_owner = info->owner();

        //Group
        m_group = info->group();

        //Owner ID
        m_owner_id = info->ownerId();

        //Group ID
        m_group_id = info->groupId();

        //Is it writable
        if(info->isWritable())
            m_writable = "Yes";
        else
            m_writable = "No";

        //Is it readable
        if(info->isReadable())
            m_readable = "Yes";
        else
            m_readable = "No";

        //Is it executable
        if(info->isExecutable())
            m_executable = "Yes";
        else
            m_executable = "No";

        infToWindow();
    }

    delete info;

}

//Sets all values on the main window
void MainWindow::infToWindow()
{
    ui->type->setText("Type: " + m_type);
    ui->size->setText("Size: " + QString::number(m_size) + " Bytes");
    ui->birth_time->setText("Birth time: " + m_birth_time);
    ui->sym_link->setText("Symbol link: " + m_symbol_link);
    ui->last_modif->setText("Last modified: " + m_last_modified);
    ui->last_read->setText("Last read: " + m_last_read);

    ui->owner->setText("Owner: " + m_owner);
    ui->group->setText("Group: " + m_group);

    ui->owner_id->setText("Owner ID: " + QString::number(m_owner_id));
    ui->group_id->setText("Group ID: " + QString::number(m_group_id));

    ui->writable->setText("Writable: " + m_writable);
    ui->readable->setText("Readable: " + m_readable);
    ui->executable->setText("Executable: " + m_executable);
}

//Sets all values to default
void MainWindow::clearInfo()
{
    ui->type->setText("Type: ");
    ui->size->setText("Size: ");
    ui->birth_time->setText("Birth time: ");
    ui->sym_link->setText("Symbol link: ");
    ui->last_modif->setText("Last modified: ");
    ui->last_read->setText("Last read: ");

    ui->owner->setText("Owner: ");
    ui->group->setText("Group: ");

    ui->owner_id->setText("Owner ID: ");
    ui->group_id->setText("Group ID: ");

    ui->writable->setText("Writable: ");
    ui->readable->setText("Readable: ");
    ui->executable->setText("Executable: ");
}