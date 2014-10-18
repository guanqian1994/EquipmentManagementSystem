#ifndef LOGIN_H
#define LOGIN_H

#include <QtWidgets\qwidget.h>
#include <QtCore\qstring.h>
#include "mainwindow.h"

namespace Ui {
	class login;
}

class login : public QWidget
{
	Q_OBJECT

public:
	explicit login(QWidget *parent = 0);
	~login();

	private slots:
	void on_loginbtn_clicked();

	void on_resetbtn_clicked();

private:
	Ui::login *ui;
	QString user;
	QString pwd;
};


#endif