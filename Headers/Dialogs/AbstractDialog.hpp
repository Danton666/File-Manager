#ifndef __ABSTRACT_DIALOG_HPP__
#define __ABSTRACT_DIALOG_HPP__

#include <QDialog>
#include <QShowEvent>

class AbstractDialog : public QDialog
{
	Q_OBJECT

protected:
	AbstractDialog(QWidget* parent = nullptr);
	~AbstractDialog();

	virtual void showEvent(QShowEvent* event) override;
};

#endif //__ABSTRACT_DIALOG_HPP__