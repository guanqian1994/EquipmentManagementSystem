#include "returnwindow.h"
#include "ui_returnwindow.h"

#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"
#include "QtCore/QList"
#include "QtWidgets/QTablewidget"


returnwindow::returnwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::returnwindow)
{
	ui->setupUi(this);
	
	ui->tableWidget->setColumnCount(7);
	list << "id" << "设备Id" << "是否借出" << "操作人员" << "时间"<<"收款"<<"备注";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	//ui->tableWidget->setColumnCount(8);
	//ui->tableWidget->setRowCount();//hang
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//row seleted
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//not allow to edit
	////let the item to the edit value
	//QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
	//int count = items.count();
	//for (int i = 0; i < count; i++)
	//{
	//	int row = ui->tableWidget->row(items.at(i));
	//	QTableWidgetItem* item = items.at(i);
	//	QString name = item->text();
	//	ui->id->setText(name);
	//}
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
	QString remark = "People:" + ui->lineEdit->text() + "," + "Remark:" + ui->textEdit->toPlainText();
	EquipmentData e;
	e._id = id.toUInt();
	//change type
	char*  ch;
	QByteArray ba = money.toLatin1();
	ch = ba.data();
	Database::get().refund(e, atoi(ch), remark);
}
void returnwindow::on_exit_clicked()
{
	this->close();
}
