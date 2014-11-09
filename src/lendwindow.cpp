#include "lendwindow.h"
#include "ui_lendwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

#include <QtWidgets/QDatetimeedit>
#include <stdlib.h>
#include <stdio.h>

lendwindow::lendwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::lendwindow)
{
	ui->setupUi(this);

	ui->dateEdit->setDateTime(QDateTime::currentDateTime());
	ui->dateEdit->setReadOnly(true);
	
}
lendwindow::~lendwindow()
{
	delete ui;
}

void lendwindow::on_ok_clicked()
{
	QString id = ui->id->text();
	EquipmentData e;
	e._id = id.toUInt();
	QString price = ui->price->text();
	char*  ch;
	QByteArray ba = price.toLatin1();
	ch = ba.data();
	QString remark = "借出单位：" + ui->lineEdit->text() + "\n" + " 经手人：" + ui->lineEdit_2->text() + "用途：" + ui->textEdit->toPlainText();
	
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定借出？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().lend(e, atof(ch), remark))
		{
			QMessageBox::information(this, tr("提示"), tr("借出成功!"), QMessageBox::Ok);
			this->close();
		}
	}
}
void lendwindow::on_exit_clicked()
{
	this->close();
}