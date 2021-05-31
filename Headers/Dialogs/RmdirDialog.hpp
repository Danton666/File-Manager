#ifndef __RMDIR_DIALOG_HPP__
#define __RMDIR_DIALOG_HPP__

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class RmdirDialog; }
QT_END_NAMESPACE

class RmdirDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::RmdirDialog* ui;

public:
	RmdirDialog(QWidget* parent = nullptr);
	~RmdirDialog();

public slots:
	void rmdir();
};

#endif //__RMDIR_DIALOG_HPP__