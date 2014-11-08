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
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//row seleted
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//not allow to edit
	LendRecord l;
	auto li = Database::get().getLendRecordList(Database::STATE_ALL, nullptr, nullptr);
	ui->tableWidget->setRowCount(li.size());
	ui->tableWidget->setColumnWidth(6, 200);
	int i = 0;
	for (auto& a : li)
	{
		SNPRINTF(_buff, BUFF_SIZE, "%d", a._id);
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(_buff));
		SNPRINTF(_buff, BUFF_SIZE, "%d", a._equipment_id);
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(_buff));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._isLend ? "Y" : "N"));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._operator));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._date));
		SNPRINTF(_buff, BUFF_SIZE, "%.2f", a._receivables);
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString((const char*)_buff)));
		ui->tableWidget->setItem(i, 6, new QTableWidgetItem(a._remark));
		i++;
	}
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
	Database::get().refund(e, atof(ch), remark);
}
void returnwindow::on_exit_clicked()
{
	this->close();
}
