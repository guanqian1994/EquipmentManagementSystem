#include "recentwindow.h"
#include "ui_recentwindow.h"

#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"
#include "QtCore/QList"
#include "QtWidgets/QTablewidget"


recentwindow::recentwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::recentwindow)
{
	ui->setupUi(this);
	ui->dateEdit_2->setDate(QDate::currentDate());
	init();
}
recentwindow::~recentwindow()
{
	delete ui;
}

void recentwindow::on_pushButton_clicked()
{
	QString start = ui->dateEdit->text();
	QString end = ui->dateEdit_2->text();
	auto li=Database::get().getLendRecordList(Database::STATE_ALL, start, end);
	ui->tableWidget->setRowCount(li.size());
	if (li.size() > 0)
	{
		QMessageBox::information(this, tr("提示"), tr("查询成功!"), QMessageBox::Ok);
		ui->tableWidget->clear();
		init();
		int i = 0;
		for (auto& a : li)
		{
			
			SNPRINTF(_buff, BUFF_SIZE, "%d", a._id);
			ui->tableWidget->setItem(i, 0, new QTableWidgetItem(_buff));
			SNPRINTF(_buff, BUFF_SIZE, "%d", a._equipment_id);
			ui->tableWidget->setItem(i, 1, new QTableWidgetItem(_buff));
			ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._isLend ? "正在借出" : "尚未借出"));
			ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._operator));
			ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._date));
			SNPRINTF(_buff, BUFF_SIZE, "%.2f", a._receivables);
			ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString((const char*)_buff)));
			ui->tableWidget->setItem(i, 6, new QTableWidgetItem(a._remark));
			i++;
		}
	}
	else
		QMessageBox::information(this, tr("提示"), tr("指定时间段内没有记录"), QMessageBox::Ok);
}
void recentwindow::on_exit_clicked()
{
	this->close();
}
void recentwindow::init()
{
	ui->tableWidget->setColumnCount(7);
	list << "id" << "设备Id" << "是否借出" << "操作人员" << "时间" << "收款" << "备注";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//row seleted
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//not allow to edit
	ui->tableWidget->setColumnWidth(6, 200);
}
