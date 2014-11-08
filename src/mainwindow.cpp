#include "mainwindow.h"

#include <cstdio>
#include <QtCore/Qtextcodec>
#include <QtWidgets/QMessagebox>
#include "ui_mainwindow.h"
#include "db_layer.h"
#include "insertwindow.h"
#include "lendwindow.h"
#include "allwindow.h"
#include "managewindow.h"
#include "returnwindow.h"
#include "recentwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(doubleclicked()));
	//TableWiget
	ui->tableWidget->setColumnCount(6);
	auto li = Database::get().getEquipmentList(0, 1000);
	ui->tableWidget->setRowCount(li.size());
	//let the line number hidden
	ui->tableWidget->verticalHeader()->setVisible(false);
	list <<"Id" << "设备名称" << "设备描述" << "登记日期" << "借出价格" << "是否借出";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(6);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//allrow
	ui->tableWidget->setMouseTracking(true);//open the mouse track
	//ui->tableWidget->setStyleSheet("selection-background-color:pink");//set the color
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//not allow to edit
	int i = 0;
	for (auto& a : li)
	{
		snprintf(_buff, BUFF_SIZE, "%d", a._id);
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(_buff));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._name));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._description));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._registrationDate));
		snprintf(_buff, BUFF_SIZE, "%.2f", a._lendPrice);
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(_buff));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(a._isLending ? "Y" : "N"));
		i++;
	}
	/*
	QHeaderView* hearderView = ui->tableWidget->verticalHeader();
	hearderView->setHidden(true);
	
	list << "Id" << "Name" << "Description" << "RegistDate" << "RegistOperator" << "Value" << "LendPrice" << "IsLending" << "RecentLendRecord" << "Image" << "Remark";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(11);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    int i = 0;

	for (auto& a : li)
	{
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
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_all_clicked()
{
	allwindow* all = new allwindow();
	all->show();
	
}
void MainWindow::on_manage_clicked()
{
	managewindow* manage = new managewindow();
	manage->show();
}
void MainWindow::on_exit_clicked()
{
	this->close();
}
void MainWindow::on_lend_clicked()
{
	lendwindow* lend = new lendwindow();
	lend->show();
}
void MainWindow::on_record_clicked()
{
	recentwindow *re = new recentwindow();
	re->show();
}
void MainWindow::on_return_2_clicked()
{
	returnwindow *ret = new returnwindow();
	ret->show();
}
void MainWindow::on_insert_clicked()
{
	insertwindow *insert = new insertwindow();
	insert->show();
}
void MainWindow::doubleclicked()
{
	QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
	items = ui->tableWidget->selectedItems();
	QString id = items.at(0)->text();
    auto li = Database::get().getEquipmentList(id.toUInt() - 1, 1, Database::STATE_ALL);

    if (li.size() && li.front()._id == id.toUInt())
    {
        allwindow *all = new allwindow();
        all->sendValue(li.front());
        all->show();
    }
	//QMessageBox::information(this, tr("提示"), a, QMessageBox::Ok);
	
	//all->setTextEditData(a);
	
	
}