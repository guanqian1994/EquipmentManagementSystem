#ifndef _LENDWINDOW_H
#define _LENDWINDOW_H

#include <QtWidgets/QDialog>

namespace Ui {
	class lendwindow;
}

class lendwindow : public QDialog
{
	Q_OBJECT

public:
	explicit lendwindow(QWidget *parent = 0);
	~lendwindow();

	private slots:
	void on_ok_clicked();
	void on_exit_clicked();

private:
	Ui::lendwindow *ui;
};

#endif 