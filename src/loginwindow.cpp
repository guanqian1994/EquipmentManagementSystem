#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

loginwindow::loginwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::loginwindow)
{
	ui->setupUi(this);
}

loginwindow::~loginwindow()
{
	delete ui;
}

void loginwindow::on_loginbtn_clicked()
{
	user = ui->user->text();
	password = ui->password->text();
	if (user.isEmpty() || password.isEmpty())
	{
		QMessageBox::information(this, tr("Error"), tr("user or password is null,please write down again!"), QMessageBox::Ok);
		return;
	}
	if (Database::get().login(user,password))
	{
		QMessageBox msg;
		msg.setText("µÇÂ¼³É¹¦£¡");
		this->hide();
		MainWindow *w = new MainWindow();
		w->show();

	}
	else
	{
		QMessageBox msg;
		msg.setText("¶Ô²»Æð£¬µÇÂ¼Ê§°Ü£¬ÇëÖØÐÂµÇÂ¼Ð»Ð»£¡");
		user.clear();
		password.clear();
	}
	
}

void loginwindow::on_resetbtn_clicked()
{
	ui->user->text().clear();
	ui->password->text().clear();
}
