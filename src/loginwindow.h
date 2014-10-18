#ifndef LOGINWINDOW_H
#define LOGICWINDOW_H

#include <QtWidgets\qdialog.h>

namespace Ui {
	class loginwindow;
}

class loginwindow : public QDialog
{
	Q_OBJECT

public:
	explicit loginwindow(QWidget *parent = 0);
	~loginwindow();

	private slots:
	void on_loginbtn_clicked();
	void on_resetbtn_clicked();

private:
	Ui::loginwindow *ui;
	QString user;
	QString password;
};

#endif 
