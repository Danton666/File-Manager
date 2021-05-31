#ifndef __FIND_DIALOG_HPP__
#define __FIND_DIALOG_HPP__

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class FindDialog; }
QT_END_NAMESPACE

class FindDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::FindDialog* ui;

public:
	FindDialog(QWidget* parent = nullptr);
	~FindDialog();
};

#endif //__FIND_DIALOG_HPP__