#include <QDir>

#include "MainWindow.hpp"
#include "Dialogs/RmdirDialog.hpp"
#include "Ui/ui_RmdirDialog.h"

RmdirDialog::RmdirDialog(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint), ui(new Ui::RmdirDialog)
{
	ui->setupUi(this);
	setWindowModality(Qt::WindowModality::WindowModal);

	connect((ui->Confirm), &QPushButton::clicked, this, &RmdirDialog::rmdir);
	connect((ui->Cancel), &QPushButton::clicked, this, &QWidget::close);
}

RmdirDialog::~RmdirDialog()
{
	delete ui;
}

void RmdirDialog::rmdir()
{
	QString dirName(((MainWindow*)parent())->current_btn->text().remove(0, 1));

	if(dirName != "..")
	{
		QDir* dir = new QDir(((MainWindow*)parent())->m_abs_path + '/' + dirName);
		dir->removeRecursively();
		delete dir;
	}

	close();
}