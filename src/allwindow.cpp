#include "allwindow.h"
#include "ui_allwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"


allwindow::allwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::allwindow)
{
	ui->setupUi(this);
	/*auto li = Database::get().getEquipmentList(0, 1000, Database::STATE_ALL);
	for (auto &a : li)
	{
		if (a._id == _id)
		{
			ui->id->setText(id);
		}

	}*/
	//ui->tableWidget->setColumnCount(11);
	////let the line number hidden
	//ui->tableWidget->verticalHeader()->setVisible(false);
	//list << "Id" << "设备名称" << "设备描述" << "登记日期" << "登记人员" << "价值" << "租出价格" << "是否借出" << "最近借出" << "设备图片" << "备注";
	//ui->tableWidget->setHorizontalHeaderLabels(list);
	////ui->tableWidget->horizontalHeader()->setStretchLastSection(11);
	//ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	//auto li = Database::get().getEquipmentList(0, 1000);
	//ui->tableWidget->setRowCount(li.size());
	//int i = 0;
	//for (auto& a : li)
	//{
 //       SNPRINTF(_buff, BUFF_SIZE, "%d", a._id);
	//	ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString((const char*)_buff)));
	//	ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._name));
	//	ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._description));
	//	ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._registrationDate));
	//	ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._registrationOperator));
 //       SNPRINTF(_buff, BUFF_SIZE, "%.2f", a._value);
 //       ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString((const char*)_buff)));
 //       SNPRINTF(_buff, BUFF_SIZE, "%.2f", a._lendPrice);
 //       ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString((const char*)_buff)));
	//	ui->tableWidget->setItem(i, 7, new QTableWidgetItem(a._isLending ? "Y" : "N"));
	//	ui->tableWidget->setItem(i, 8, new QTableWidgetItem(a._recentLendRecord));
	//	ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QIcon(""), ""));
	//	ui->tableWidget->setItem(i, 10, new QTableWidgetItem(a._remark));
	//	i++;
	//}
}
allwindow::~allwindow()
{
	delete ui;
}

void allwindow::on_update_clicked()
{

}
void allwindow::on_exit_clicked()
{
	this->close();
}
void allwindow::on_delete_2_clicked()
{

}
void allwindow::sendValue(EquipmentData& equipment)
{
	snprintf(_buff, BUFF_SIZE, "%d", equipment._id);
	ui->id->setText(_buff);
	ui->name->setText(equipment._name);
	ui->description->setText(equipment._description);
	ui->date->setText(equipment._registrationDate);
	ui->people->setText(equipment._registrationOperator);
	snprintf(_buff, BUFF_SIZE, "%.2f", equipment._value);
	ui->value->setText(_buff);
	snprintf(_buff, BUFF_SIZE, "%.2f", equipment._lendPrice);
	ui->price->setText(_buff);
	
	ui->pic->setPixmap(QPixmap::fromImage(equipment._image));
	ui->pic->setVisible(true);
	ui->islend->setText(equipment._isLending?"借出中":"尚未借出");
	ui->remark->setText(equipment._remark);
}