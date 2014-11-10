#include "returnwindow.h"
#include "ui_returnwindow.h"

#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "QtCore/QList"
#include "QtWidgets/QTablewidget"


returnwindow::returnwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::returnwindow)
{
	ui->setupUi(this);
	ui->dateEdit->setDateTime(QDateTime::currentDateTime());
	ui->dateEdit->setReadOnly(true);
}
returnwindow::~returnwindow()
{ 
	delete ui;
}

void returnwindow::on_ok_clicked()
{
	QString id = ui->id->text();
	QString money = ui->money->text();
	QString remark = "������Ա:" + ui->lineEdit->text() + "," + "��ע:" + ui->textEdit->toPlainText();
	EquipmentData e;
	e._id = id.toUInt();
	//change type
	char*  ch;
	QByteArray ba = money.toLatin1();
	ch = ba.data();
	QMessageBox msg(QMessageBox::NoIcon, tr("��ʾ"), tr("ȷ���黹��"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().refund(e, atof(ch), remark))
			QMessageBox::information(this, tr("��ʾ"), tr("�黹�ɹ�!"), QMessageBox::Ok);
	}
}
void returnwindow::on_exit_clicked()
{
	this->close();
}
