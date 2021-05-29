#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

#include <QMainWindow>
#include <QFileInfo>
#include <QPushButton>
#include <QLabel>

#include <QKeyEvent>
#include <QCloseEvent>

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

    QString m_btnStyle;
    
    QVector<QPushButton*> m_flist;

    QFileInfoList* m_list;

    QString m_abs_path;

private:
    void posLenForPath(QLabel* path, const QString& new_path);
    void clearLayout();

protected:
    void keyPressEvent(QKeyEvent* e);
    void closeEvent(QCloseEvent* e);


public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    Ui::MainWindow* getUi();
    QuitDialog* getQuitDialog();
    QFileInfoList* getListOfDir();
    QVector<QPushButton*> getButtonList();

    QFileInfoList* DirContent(const QString& path);
    void setDirContent(const QString& cd);


public slots:
    void changeDir();

};

#endif //__MAIN_WINDOW_HPP__