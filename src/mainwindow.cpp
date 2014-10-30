#include "mainwindow.h"

#include <cstdio>
#include <QtCore/Qtextcodec>
#include "ui_mainwindow.h"
#include "db_layer.h"
#include "insertwindow.h"
#include "lendwindow.h"
#include "allwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	//TableWiget
	ui->tableWidget->setColumnCount(6);
	auto li = Database::get().getEquipmentList(0, 1000);
	ui->tableWidget->setRowCount(li.size());
	//let the line number hidden
	ui->tableWidget->verticalHeader()->setVisible(true);
	list << "Name" << "Description" << "RegistDate" << "LendPrice" << "IsLend"<<"Image";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(6);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//allrow
	ui->tableWidget->setMouseTracking(true);//open the mouse track
	ui->tableWidget->setStyleSheet("selection-background-color:pink");//set the color
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//not allow to edit
	int i = 0;
	for (auto& a : li)
	{
		snprintf(_buff3, BUFF_SIZE, "%d", a._lendPrice);
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(a._name));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._description));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._registrationDate));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString((const char*)_buff3)));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._isLending ? "Y" : "N"));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QIcon(""), ""));
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

}
void MainWindow::on_return_clicked()
{

}
void MainWindow::on_insert_clicked()
{
	insertwindow *insert = new insertwindow();
	insert->show();
}


