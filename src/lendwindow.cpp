#include "lendwindow.h"
#include "ui_lendwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

#include <QtWidgets/QDatetimeedit>

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
	QString remark = "�����λ��" + ui->lineEdit->text() + "\n" + " �����ˣ�" + ui->lineEdit_2->text() + "\n" + "��;��" + ui->textEdit->toPlainText();
	Database::get().lend(e, price.toUInt(), remark);
	//QMessageBox::information(this, tr("��ʾ"), tr("chenggong"), QMessageBox::Ok);
	//this->close();
}
void lendwindow::on_exit_clicked()
{

}