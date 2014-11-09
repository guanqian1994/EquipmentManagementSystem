#include "mainwindow.h"

#include <cstdio>
#include <QtCore/Qtextcodec>
#include <QtWidgets/QMessagebox>
#include "ui_mainwindow.h"
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
	init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_all_clicked()
{
	ui->tableWidget->clear();
	init();
}
void MainWindow::on_manage_clicked()
{
	managewindow* manage = new managewindow();
	manage->show();
}
void MainWindow::on_exit_clicked()
{
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定退出？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		this->close();
	}
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
	auto li = Database::get().getEquipmentList(0, 1000, Database::STATE_ALL);
	for (auto &a : li)
	{
		if (a._id == id.toUInt())
		{
			allwindow *all = new allwindow();
			all->sendValue(a);
			all->show();
		}
	}
}
void MainWindow::init()
{
	li = Database::get().getEquipmentList(0, 1000);
	//TableWiget
	ui->tableWidget->setColumnCount(6);
	ui->tableWidget->setRowCount(li.size());
	//let the line number hidden
	ui->tableWidget->verticalHeader()->setVisible(false);
	list << "Id" << "设备名称" << "设备描述" << "登记日期" << "借出价格" << "是否借出";
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
}
void MainWindow::on_about_clicked()
{
	QString about = "版本：  V1.0(乞丐版)\n组员：龙晨    补子畅";
	QMessageBox msg(QMessageBox::NoIcon, tr("关于--设备管理系统"),about);
	msg.setIconPixmap(QPixmap("icon1.png"));
	msg.exec();
}