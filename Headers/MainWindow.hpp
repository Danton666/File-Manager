#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

#include <QMainWindow>
#include <QFileInfo>
#include <QPushButton>

#include <QKeyEvent>
#include <QCloseEvent>
#include <QFocusEvent>

#include "Dialogs/QuitDialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QuitDialog* quitDg;
    
    QVector<QPushButton*> m_flist;

    QFileInfoList* m_list;

protected:
    void keyPressEvent(QKeyEvent* e);
    void closeEvent(QCloseEvent* e);
    void focusInEvent(QFocusEvent* e);

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    Ui::MainWindow* getUi();

    QFileInfoList* DirContent(const QString& path);
    QFileInfoList* getListOfDir();

    QuitDialog* getQuitDialog();
    QVector<QPushButton*> getButtonList();

};

#endif //__MAIN_WINDOW_HPP__