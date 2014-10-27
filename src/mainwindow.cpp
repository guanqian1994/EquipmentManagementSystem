#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/Qtextcodec>
#include "db_layer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	//TableWiget
	ui->tableWidget->setColumnCount(10);
	list << "Name" << "Description" << "RegistrationDate" << "RegistrationOperator" << "Value" << "LendPrice" << "IsLending" << "RecentLendRecord" << "Image" << "Remark";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(9);
	/*auto li = Database::get().getEquipmentList(0, 1000);
	for (int i = 0;li.size(); i++)
	{
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(li[i]._name));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(li[i]._description));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(li[i]._registrationDate));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(li[i]._registrationOperator));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(li[i]._value));
		ui->tableWidget->setItem(i, 5, new QTableWidgetItem(li[i]._lendPrice));
		ui->tableWidget->setItem(i, 6, new QTableWidgetItem(li[i]._isLending));
		ui->tableWidget->setItem(i, 7, new QTableWidgetItem(li[i]._recentLendRecord));
		ui->tableWidget->setItem(i, 8, new QTableWidgetItem(""));
		ui->tableWidget->setItem(i, 9, new QTableWidgetItem(li[i]._remark));
		
	}*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
