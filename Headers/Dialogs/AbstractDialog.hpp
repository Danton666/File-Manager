#ifndef __ABSTRACT_DIALOG_HPP__
#define __ABSTRACT_DIALOG_HPP__

#include <QDialog>

class AbstractDialog : public QDialog
{
	Q_OBJECT

protected:
	AbstractDialog(QWidget* parent = nullptr);
	~AbstractDialog();
};

#endif //__ABSTRACT_DIALOG_HPP__