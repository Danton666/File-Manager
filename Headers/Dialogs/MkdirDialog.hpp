#ifndef __MKDIR_DIALOG_HPP__
#define __MKDIR_DIALOG_HPP__

// #include <QDialog>
#include "Dialogs/AbstractDialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MkdirDialog; }
QT_END_NAMESPACE

class MkdirDialog : public AbstractDialog
{
	Q_OBJECT

private:
	Ui::MkdirDialog* ui;

	bool check_dir;

public:
	MkdirDialog(QWidget* parent = nullptr);
	~MkdirDialog();

	const Ui::MkdirDialog* getUi() const;


public slots:
	void mkdir();
	void chkdir();
};

#endif //__MKDIR_DIALOG_HPP__