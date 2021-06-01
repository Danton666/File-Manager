#include <QDir>
#include <QFile>
// #include <QtDebug>

#include "MainWindow.hpp"

#include "Dialogs/CopyDialog.hpp"
#include "Ui/ui_CopyDialog.h"

CopyDialog::CopyDialog(QWidget* parent) : AbstractDialog(parent), ui(new Ui::CopyDialog)
{
	ui->setupUi(this);

	connect((ui->lineEdit), &QLineEdit::textEdited, this, &CopyDialog::chkdir);

	connect((ui->Confirm), &QPushButton::clicked, this, &CopyDialog::cp);
	connect((ui->Cancel), &QPushButton::clicked, this, &QWidget::close);
}

CopyDialog::~CopyDialog() { delete ui; }

//Slots
void CopyDialog::cp()
{
	QString name(((MainWindow*)parent())->current_btn->text().remove(0, 1));
	QString path(((MainWindow*)parent())->m_abs_path + '/' + name);
	QString dest(ui->lineEdit->text());

	QFileInfo* entry = new QFileInfo(path);

	if(name != ".." && check_dest)
	{
		if(entry->isDir())
		{
			// QDir* dir = new QDir(path);

			// dir->setSorting(QDir::Name);
			// dir->setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoDot);

			// QFileInfoList* list = dir->entryInfoList();

			// for(int i = 0; i < list->size(); ++i)
			// {

			// }
			// delete dir;
		}
		else
		{
			QFile* file = new QFile(path);
			file->copy(dest + '/' + name);
			delete file;
		}
	}
	delete entry;

	close();
}

void CopyDialog::chkdir()
{
	QString dirName = ui->lineEdit->text();

	if(!QDir(dirName).exists())
	{
		check_dest = false;
		ui->lineEdit->setStyleSheet("QLineEdit{font:25px'Ubuntu';} QLineEdit{color:red;}");
	}
	else
	{
		check_dest = true;
		ui->lineEdit->setStyleSheet("QLineEdit{font:25px'Ubuntu';} QLineEdit{color:green;}");
	}
}