#ifndef __QUIT_DIALOG_HPP__
#define __QUIT_DIALOG_HPP__

// #include <QDialog>
#include "Dialogs/AbstractDialog.hpp"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class QuitDialog; }
QT_END_NAMESPACE

class QuitDialog : public AbstractDialog
{
    Q_OBJECT

private:
    Ui::QuitDialog *ui;

public:
    explicit QuitDialog(QWidget* parent = nullptr);
    ~QuitDialog();

public:
    Ui::QuitDialog* getUi();

    QPushButton* getYes();
    QPushButton* getNo();



};

#endif //__QUIT_DIALOG_HPP__