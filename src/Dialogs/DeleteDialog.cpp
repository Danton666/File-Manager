#include <QDir>
// #include <QtDebug>

#include "MainWindow.hpp"

#include "Dialogs/DeleteDialog.hpp"
#include "Ui/ui_DeleteDialog.h"

DeleteDialog::DeleteDialog(QWidget* parent) : AbstractDialog(parent), ui(new Ui::DeleteDialog)
{
	ui->setupUi(this);

	connect((ui->Confirm), &QPushButton::clicked, this, &DeleteDialog::del);
	connect((ui->Cancel), &QPushButton::clicked, this, &QWidget::close);
}

DeleteDialog::~DeleteDialog()
{
	delete ui;
}

void DeleteDialog::del()
{
	QString name(((MainWindow*)parent())->current_btn->text().remove(0, 1));
	QString path(((MainWindow*)parent())->m_abs_path + '/' + name);

	QFileInfo* entry = new QFileInfo(path);

	if(name != "..")
	{
		if(entry->isDir())
		{
			QDir* dir = new QDir(path);
			dir->removeRecursively();
			delete dir;
		}
		else
		{
			QFile* file = new QFile(path);
			file->remove();
			delete file;
		}
	}
	delete entry;

	close();
}