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
	connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(slotItemclicked()));
	init();
}
managewindow::~managewindow()
{
	delete ui;
}

void managewindow::on_insert_clicked()
{
	QString name = ui->name->text();
	QString description = ui->description->text();
	QString people = ui->people->text();
	QString value = ui->value->text();
	QString price = ui->price->text();
	QString remark = ui->remark->toPlainText();
	QString time = ui->dateEdit->text();
	QString Id = ui->spinBox->text();
	EquipmentData e{ Id.toUInt(), name, description, time, people, value.toFloat(), price.toFloat(), 0, 0, QImage(), remark };
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定采购？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().registration(e))
		{
			QMessageBox::information(this, tr("提示"), tr("成功采购设备!"), QMessageBox::Ok);
			ui->tableWidget->clear();
			init();
		}
	}
}

void managewindow::on_update_clicked()
{
	QString name=ui->name->text();
	QString description=ui->description->text();
	QString people=ui->people->text();
	QString value = ui->value->text();
	QString price = ui->price->text();
	QString remark = ui->remark->toPlainText();
	QString time = ui->dateEdit->text();
	QString Id = ui->spinBox->text();
	//snprintf(_buff, BUFF_SIZE, Id);
	EquipmentData e{ Id.toUInt(), name, description, time, people, value.toFloat(), price.toFloat(), 0, 0, QImage(), remark };
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定修改？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().updateEquipment(e))
		{
			QMessageBox::information(this, tr("提示"), tr("修改设备成功!"), QMessageBox::Ok);
			ui->tableWidget->clear();
			init();
		}
	}
}
void managewindow::on_delete_2_clicked()
{
	QString id = ui->spinBox->text();
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定删除？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().deleteEquipment(id.toUInt()))
		{
			QMessageBox::information(this, tr("提示"), tr("删除设备成功!"), QMessageBox::Ok);
			ui->tableWidget->clear();
			init();
		}
	}
}
void managewindow::on_exit_clicked()
{
	this->close();
}
void managewindow::slotItemclicked()
{
	QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
	items = ui->tableWidget->selectedItems();
	QString _id = items.at(0)->text();
	QString _name = items.at(1)->text();
	QString _description = items.at(2)->text();
	QString _registrationOperator = items.at(4)->text();
	QString _value = items.at(5)->text();
	QString _lendPrice = items.at(6)->text();
	QString _rem = items.at(8)->text();
	ui->spinBox->setValue(_id.toUInt());
	ui->name->setText(_name);
	ui->description->setText(_description);
	ui->people->setText(_registrationOperator);
	ui->value->setText(_value);
	ui->price->setText(_lendPrice);
	ui->remark->setPlainText(_rem);
}
void managewindow::init()
{
	ui->tableWidget->setColumnCount(11);
	//let the line number hidden
	ui->tableWidget->verticalHeader()->setVisible(false);
	list << "Id" << "设备名称" << "设备描述" << "登记日期" << "登记人员" << "价值" << "租出价格" << "是否借出" << "备注";
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
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString((const char*)_buff)));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._name));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._description));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._registrationDate));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._registrationOperator));
		snprintf(_buff, BUFF_SIZE, "%f", a._value);
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString((const char*)_buff)));
		snprintf(_buff, BUFF_SIZE, "%f", a._lendPrice);
		ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString((const char*)_buff)));
		ui->tableWidget->setItem(i, 7, new QTableWidgetItem(a._isLending ? "Y" : "N"));
		ui->tableWidget->setItem(i, 8, new QTableWidgetItem(a._remark));
		i++;
	}

	ui->dateEdit->setDate(QDate::currentDate());
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}