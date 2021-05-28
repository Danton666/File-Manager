#include <QPushButton>
#include <QApplication>

#include "Dialogs/QuitDialog.hpp"
#include "Ui/ui_QuitDialog.h"

QuitDialog::QuitDialog(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint), ui(new Ui::QuitDialog)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModality::WindowModal);

    connect((ui->Yes), &QPushButton::clicked, this, &QuitDialog::closeApp);
    connect((ui->No), &QPushButton::clicked, this, &QWidget::close);
}

QuitDialog::~QuitDialog() { delete ui; }

void QuitDialog::closeApp()
{
	this->close();
	parentWidget()->close();
	qApp->quit();
}

Ui::QuitDialog* QuitDialog::getUi() { return ui; }

QPushButton* QuitDialog::getYes() { return ui->Yes; }
QPushButton* QuitDialog::getNo() { return ui->No; }