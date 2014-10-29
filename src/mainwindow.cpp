#include "mainwindow.h"

#include <cstdio>
#include <QtCore/Qtextcodec>
#include "ui_mainwindow.h"
#include "db_layer.h"
#include "insertwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	//TableWiget
	ui->tableWidget->setColumnCount(11);
	auto li = Database::get().getEquipmentList(0, 1000);
	ui->tableWidget->setRowCount(li.size());
	//let the line number hidden
	ui->tableWidget->verticalHeader()->setVisible(false);
	/*QHeaderView* hearderView = ui->tableWidget->verticalHeader();
	hearderView->setHidden(true);*/
	list << "Id" << "Name" << "Description" << "RegistDate" << "RegistOperator" << "Value" << "LendPrice" << "IsLending" << "RecentLendRecord" << "Image" << "Remark";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(11);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	/*
	auto li = Database::get().getEquipmentList(0, 1000);
	ui->tableWidget->setRowCount(li.size());
	for (int i = 0;i<li.size(); i++)
	{
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem());
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(li[i]._name));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(li[i]._description));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(li[i]._registrationDate));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(li[i]._registrationOperator));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(li[i]._value));
		ui->tableWidget->setItem(i, 6, new QTableWidgetItem(li[i]._lendPrice));
		ui->tableWidget->setItem(i, 7, new QTableWidgetItem(li[i]._isLending));
		ui->tableWidget->setItem(i, 8, new QTableWidgetItem(li[i]._recentLendRecord));
		ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QIcon(""),""));
		ui->tableWidget->setItem(0, 10, new QTableWidgetItem(li[0]._remark));
	}
	*/
    int i = 0;

		for (auto& a : li)
		{
            std::snprintf(_buff, BUFF_SIZE, "%d", a._id);
			ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString((const char*)_buff)));
			ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._name));
			ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._description));
			ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._registrationDate));
			ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._registrationOperator));
			ui->tableWidget->setItem(i, 5, new QTableWidgetItem(a._value));
			ui->tableWidget->setItem(i, 6, new QTableWidgetItem(a._lendPrice));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(a._isLending ? "Y" : "N"));
			ui->tableWidget->setItem(i, 8, new QTableWidgetItem(a._recentLendRecord));
			ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QIcon(""), ""));
			ui->tableWidget->setItem(0, 10, new QTableWidgetItem(a._remark));
            i++;
		}

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_all_clicked()
{
	auto li = Database::get().getEquipmentList(0, 1000);
	ui->tableWidget->setRowCount(li.size());
	for (int i = 0; i <Database::get().getEquipmentCount(); i++)
	{
		for (auto& a : li)
		{
			ui->tableWidget->setItem(i, 0, new QTableWidgetItem(a._id));
			ui->tableWidget->setItem(i, 1, new QTableWidgetItem(a._name));
			ui->tableWidget->setItem(i, 2, new QTableWidgetItem(a._description));
			ui->tableWidget->setItem(i, 3, new QTableWidgetItem(a._registrationDate));
			ui->tableWidget->setItem(i, 4, new QTableWidgetItem(a._registrationOperator));
			ui->tableWidget->setItem(i, 5, new QTableWidgetItem(a._value));
			ui->tableWidget->setItem(i, 6, new QTableWidgetItem(a._lendPrice));
			ui->tableWidget->setItem(i, 7, new QTableWidgetItem(a._isLending));
			ui->tableWidget->setItem(i, 8, new QTableWidgetItem(a._recentLendRecord));
			ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QIcon(""), ""));
			ui->tableWidget->setItem(0, 10, new QTableWidgetItem(a._remark));
		}
	}
}
void MainWindow::on_exit_clicked()
{

}
void MainWindow::on_lend_clicked()
{

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


