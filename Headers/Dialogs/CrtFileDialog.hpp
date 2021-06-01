#ifndef __CRT_FILE_DIALOG_HPP__
#define __CRT_FILE_DIALOG_HPP__

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CrtFileDialog; }
QT_END_NAMESPACE

class CrtFileDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::CrtFileDialog* ui;

	bool check_file;

public:
	CrtFileDialog(QWidget* parent = nullptr);
	~CrtFileDialog();

public slots:
	void crfile();
	void chkfile();
};

#endif //__CRT_FILE_DIALOG_HPP__