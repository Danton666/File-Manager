#ifndef __MKDIR_DIALOG_HPP__
#define __MKDIR_DIALOG_HPP__

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MkdirDialog; }
QT_END_NAMESPACE

class MkdirDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::MkdirDialog* ui;

	bool check_dir;

private:
	void makeDir(const QString& path);

public:
	MkdirDialog(QWidget* parent = nullptr);
	~MkdirDialog();

	const Ui::MkdirDialog* getUi() const;


public slots:
	void mkdir();
	void chkdir();
};

#endif //__MKDIR_DIALOG_HPP__