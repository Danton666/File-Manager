#ifndef __COPY_DIALOG_HPP__
#define __COPY_DIALOG_HPP__

#include "Dialogs/AbstractDialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CopyDialog; }
QT_END_NAMESPACE

class CopyDialog : public AbstractDialog
{
	Q_OBJECT

private:
	Ui::CopyDialog* ui;
	bool check_dest;

public:
	CopyDialog(QWidget* parent = nullptr);
	~CopyDialog();

public slots:
	void chkdir();
	void cp();
};

#endif //__COPY_DIALOG_HPP__