#ifndef _ALLWINDOW_H
#define _ALLWINDOW_H

#define BUFF_SIZE 24

#include <QtWidgets/QDialog>

namespace Ui {
	class allwindow;
}

class allwindow : public QDialog
{
	Q_OBJECT

public:
	explicit allwindow(QWidget *parent = 0);
	~allwindow();

	private slots:
	void on_ok_clicked();
	void on_exit_clicked();

private:
	Ui::allwindow *ui;
	QStringList list;
	char _buff[BUFF_SIZE];
	char _buff2[BUFF_SIZE];
	char _buff3[BUFF_SIZE];
};

#endif 