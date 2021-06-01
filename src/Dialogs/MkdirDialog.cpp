#include <QDir>

#include "MainWindow.hpp"

#include "Dialogs/MkdirDialog.hpp"
#include "Ui/ui_MkdirDialog.h"


MkdirDialog::MkdirDialog(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint), ui(new Ui::MkdirDialog)
{
	check_dir = false;

	ui->setupUi(this);

	setWindowModality(Qt::WindowModality::WindowModal);

	connect((ui->lineEdit), &QLineEdit::textEdited, this, &MkdirDialog::chkdir);

	connect((ui->Cancel), &QPushButton::clicked, this, &QWidget::close);
	connect((ui->Confirm), &QPushButton::clicked, this, &MkdirDialog::mkdir);
}

MkdirDialog::~MkdirDialog() 
{
	delete ui;
}

const Ui::MkdirDialog* MkdirDialog::getUi() const { return ui; }

//Slots
void MkdirDialog::mkdir()
{
	if(check_dir)
	{
		// makeDir(((MainWindow*)parent())->m_abs_path);
		QDir* dir = new QDir(((MainWindow*)parent())->m_abs_path);

		dir->mkdir(ui->lineEdit->text());

		delete dir;
		close();
	}
}

void MkdirDialog::chkdir()
{
	QString dirName = ui->lineEdit->text();

	if(QDir(((MainWindow*)parent())->m_abs_path + '/' + dirName).exists())
	{
		check_dir = false;
		ui->lineEdit->setStyleSheet("QLineEdit{font:25px'Ubuntu';} QLineEdit{color:red;}");
	}
	else
	{
		check_dir = true;
		ui->lineEdit->setStyleSheet("QLineEdit{font:25px'Ubuntu';} QLineEdit{color:green;}");
	}
}