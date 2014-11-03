#include "managewindow.h"
#include "ui_managewindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

managewindow::managewindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::managewindow)
{
	ui->setupUi(this);
	ui->tableWidget->setColumnCount(11);
	//let the line number hidden
	ui->tableWidget->verticalHeader()->setVisible(false);
	list << "Id" << "�豸����" << "�豸����" << "�Ǽ�����" << "�Ǽ���Ա" << "��ֵ" << "����۸�" << "�Ƿ���" << "������" << "�豸ͼƬ" << "��ע";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	//ui->tableWidget->horizontalHeader()->setStretchLastSection(11);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	auto li = Database::get().getEquipmentList(0, 1000);
	ui->tableWidget->setRowCount(li.size());
	int i = 0;
	
	for (auto& a : li)
	{
		//buff to zifuzhuanhuan
		snprintf(_buff, BUFF_SIZE, "%d", a._id);
		snprintf(_buff2, BUFF_SIZE, "%d", a._value);
		snprintf(_buff3, BUFF_SIZE, "%d", a._lendPrice);
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString((const char*)_buff)));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._name));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._description));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._registrationDate));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._registrationOperator));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString((const char*)_buff2)));
		ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString((const char*)_buff3)));
		ui->tableWidget->setItem(i, 7, new QTableWidgetItem(a._isLending ? "Y" : "N"));
		ui->tableWidget->setItem(i, 8, new QTableWidgetItem(a._recentLendRecord));
		ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QIcon(""), ""));
		ui->tableWidget->setItem(i, 10, new QTableWidgetItem(a._remark));
		i++;
	}
	//let the item to the edit value
	QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
	
	QString names = items.at(0)->text();;
	int count = items.count();
	
	ui->name->setText(names);
}
managewindow::~managewindow()
{
	delete ui;
}

void managewindow::on_update_clicked()
{
	QString name=ui->name->text();
	QString description=ui->description->text();
	QString people=ui->people->text();
	QString value = ui->value->text();
	QString price = ui->price->text();
	QString remark = ui->price->text();
	QDateTime time = ui->dateEdit->dateTime();
	EquipmentData e{0,name,description,time,people,value,price,,}
	//Database::get().updateEquipment();
}
void managewindow::on_delete_2_clicked()
{

}
void managewindow::on_exit_clicked()
{
	this->close();
}