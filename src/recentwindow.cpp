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
		QMessageBox::information(this, tr("��ʾ"), tr("��ѯ�ɹ�!"), QMessageBox::Ok);
		ui->tableWidget->clear();
		init();
		int i = 0;
		for (auto& a : li)
		{
			
			SNPRINTF(_buff, BUFF_SIZE, "%d", a._id);
			ui->tableWidget->setItem(i, 0, new QTableWidgetItem(_buff));
			SNPRINTF(_buff, BUFF_SIZE, "%d", a._equipment_id);
			ui->tableWidget->setItem(i, 1, new QTableWidgetItem(_buff));
			ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._isLend ? "���ڽ��" : "��δ���"));
			ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._operator));
			ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._date));
			SNPRINTF(_buff, BUFF_SIZE, "%.2f", a._receivables);
			ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString((const char*)_buff)));
			ui->tableWidget->setItem(i, 6, new QTableWidgetItem(a._remark));
			i++;
		}
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("ָ��ʱ�����û�м�¼"), QMessageBox::Ok);
}
void recentwindow::on_exit_clicked()
{
	this->close();
}
void recentwindow::init()
{
	ui->tableWidget->setColumnCount(7);
	list << "id" << "�豸Id" << "�Ƿ���" << "������Ա" << "ʱ��" << "�տ�" << "��ע";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//row seleted
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//not allow to edit
	ui->tableWidget->setColumnWidth(6, 200);
}
