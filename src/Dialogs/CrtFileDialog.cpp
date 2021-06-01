#include <QFile>

#include "MainWindow.hpp"

#include "Dialogs/CrtFileDialog.hpp"
#include "Ui/ui_CrtFileDialog.h"

CrtFileDialog::CrtFileDialog(QWidget* parent) : AbstractDialog(parent), ui(new Ui::CrtFileDialog)
{
	check_file = false;

	ui->setupUi(this);

	connect((ui->lineEdit), &QLineEdit::textEdited, this, &CrtFileDialog::chkfile);

	connect((ui->Cancel), &QPushButton::clicked, this, &QWidget::close);
	connect((ui->Confirm), &QPushButton::clicked, this, &CrtFileDialog::crfile);
}

CrtFileDialog::~CrtFileDialog() { delete ui; }

//Slots
void CrtFileDialog::crfile()
{
	QString fileName = ui->lineEdit->text();

	if(check_file)
	{
		QFile* file = new QFile(((MainWindow*)parent())->m_abs_path + '/' + fileName);

		file->open(QIODevice::NewOnly);
		file->close();

		delete file;
		close();
	}
}

void CrtFileDialog::chkfile()
{
	QString fileName = ui->lineEdit->text();

	if(QFile(((MainWindow*)parent())->m_abs_path + '/' + fileName).exists())
	{
		check_file = false;
		ui->lineEdit->setStyleSheet("QLineEdit{font:25px'Ubuntu';} QLineEdit{color:red;}");
	}
	else
	{
		check_file = true;
		ui->lineEdit->setStyleSheet("QLineEdit{font:25px'Ubuntu';} QLineEdit{color:green;}");
	}
}