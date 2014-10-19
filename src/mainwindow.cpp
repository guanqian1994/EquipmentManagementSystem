#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore\qtextcodec.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	//TableWiget
	ui->tableWidget->setColumnCount(10);
	list << "设备名称" << "SHEBEIMIAOSHU" << "DENGJIRIQI" << "DENGJICAOZUOYUAN" << "JIAZHI" << "CHUZUJIAGE" << "SHEBEIZHUANGTAI" << "ZUIJINYICIJIECHUJIELU" << "SHEBEITUPIAN" << "BEIZHU";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(10);
	/*
	//设置每列的宽度
	for (int i=0; i <= ui->tableWidget->rowCount(); i++)
		ui->tableWidget->setColumnWidth(i, 200);
		*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
