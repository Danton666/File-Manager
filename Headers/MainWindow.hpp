#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

#include <QMainWindow>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <QEvent>
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

    QPushButton* current_btn;

    //Info
    QString m_type;
    qint64 m_size;
    QString m_birth_time;
    QString m_symbol_link;
    QString m_last_modified;
    QString m_last_read;

    QString m_owner;
    QString m_group;
    uint m_owner_id;
    uint m_group_id;

    QString m_writable;
    QString m_readable;
    QString m_executable; 

    //hot keys
    bool ctrl_i;

private:
    void posLenForPath(QLabel* path, const QString& new_path);
    void clearLayout();
    void cd(const QPushButton* button);

    void setInfo(const QPushButton* button);
    void clearInfo();
    void infToWindow();

protected:
    void keyPressEvent(QKeyEvent* e);
    void closeEvent(QCloseEvent* e);

    bool eventFilter(QObject* obj, QEvent* event) override;


public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    Ui::MainWindow* getUi();
    QuitDialog* getQuitDialog();
    QFileInfoList* getListOfDir();
    QVector<QPushButton*> getButtonList();

    QFileInfoList* DirContent(const QString& path);
    void setDirContent(const QString& cd = ".", QVBoxLayout* vbox = nullptr);


public slots:
    void changeDir();

};

#endif //__MAIN_WINDOW_HPP__