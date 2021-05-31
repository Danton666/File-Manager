#include "MainWindow.hpp"

#include "Dialogs/MkdirDialog.hpp"
#include "Ui/ui_MkdirDialog.h"

#include <QDir>

MkdirDialog::MkdirDialog(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint), ui(new Ui::MkdirDialog)
{
	ui->setupUi(this);

	setWindowModality(Qt::WindowModality::WindowModal);

	connect((ui->Cancel), &QPushButton::clicked, this, &QWidget::close);
	connect((ui->Confirm), &QPushButton::clicked, this, &MkdirDialog::mkdir);
}

MkdirDialog::~MkdirDialog() 
{
	delete ui;
}

const Ui::MkdirDialog* MkdirDialog::getUi() const { return ui; }

void MkdirDialog::makeDir(const QString& path)
{
	QDir* dir = new QDir(path);
	dir->mkdir(ui->lineEdit->text());
}

void MkdirDialog::mkdir()
{
	makeDir(((MainWindow*)parent())->m_abs_path);

	close();
}