#include "loginwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <stdlib.h>
#include <Windows.h>

Logic::Logic(QWidget *parent) :
QWidget(parent),
ui(new Ui::Logic)
{
	ui->setupUi(this);
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap("3.jpg")));
	this->setPalette(palette);
}

Logic::~Logic()
{
	delete ui;
}

void Logic::on_pushButton_enter_clicked()
{
	if (ui->lineEdit_pwd->text().isEmpty() || ui->lineEdit_pwd->text().isEmpty())
	{
		QMessageBox::information(this, tr("warn"), tr("Please enter your whole information!"), QMessageBox::Ok);
		return;
	}
	user = ui->lineEdit_user->text();
	pwd = ui->lineEdit_pwd->text();
	QString correctuser = "10011006";
	QString correctpwd = "0";
	qDebug() << correctuser << correctpwd;
	if (user == correctuser && pwd == correctpwd)
	{
		this->hide();
		//sleep(100);
		MainWindow *w = new MainWindow();
		w->show();

	}
	else
	{
		QMessageBox::warning(this, tr("warn"), tr("Please check your user and password!"), QMessageBox::Ok);
		ui->lineEdit_user->clear();
		ui->lineEdit_pwd->clear();
	}
}

void Logic::on_pushButton_cancel_clicked()
{
	ui->lineEdit_user->clear();
	ui->lineEdit_pwd->clear();
}

void Logic::on_pushButton_out_clicked()
{
	this->close();
}
