#include "Dialogs/AbstractDialog.hpp"

AbstractDialog::AbstractDialog(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint) 
{
	setWindowModality(Qt::WindowModality::WindowModal);
}
AbstractDialog::~AbstractDialog() {}