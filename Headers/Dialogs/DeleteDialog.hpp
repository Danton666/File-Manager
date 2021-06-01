#ifndef __DELETE_DIALOG_HPP__
#define __DELETE_DIALOG_HPP__

#include "Dialogs/AbstractDialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DeleteDialog; }
QT_END_NAMESPACE

class DeleteDialog : public AbstractDialog
{
	Q_OBJECT

private:
	Ui::DeleteDialog* ui;

public:
	DeleteDialog(QWidget* parent = nullptr);
	~DeleteDialog();

public slots:
	void del();
};

#endif //__DELETE_DIALOG_HPP__