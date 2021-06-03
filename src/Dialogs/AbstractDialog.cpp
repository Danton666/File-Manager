#include "Dialogs/AbstractDialog.hpp"

AbstractDialog::AbstractDialog(QWidget* parent) : QDialog(parent, Qt::FramelessWindowHint) 
{
	setWindowModality(Qt::WindowModality::WindowModal);
}
AbstractDialog::~AbstractDialog() {}

void AbstractDialog::showEvent(QShowEvent* event) { QDialog::showEvent(event); }