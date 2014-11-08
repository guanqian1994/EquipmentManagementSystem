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
	ui->password->setEchoMode(QLineEdit::Password);
	ui->user->setPlaceholderText("请输入用户名");
	ui->password->setPlaceholderText("请输入密码");
	ui->user->setText("admin");
	ui->password->setText("123456");
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
		this->hide();
		QMessageBox::information(this, tr("Login"), tr("Login sucessed!"), QMessageBox::Ok);
		MainWindow *w = new MainWindow();
		w->show();

	}
	else
	{
		QMessageBox::information(this, tr("Login"), tr("Login failed~~"), QMessageBox::Ok);
		ui->user->clear();
		ui->password->clear();
	}
}

void loginwindow::on_resetbtn_clicked()
{
	ui->user->clear();
	ui->password->clear();
}
