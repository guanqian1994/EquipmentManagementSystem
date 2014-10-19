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
	list << "�豸����" << "SHEBEIMIAOSHU" << "DENGJIRIQI" << "DENGJICAOZUOYUAN" << "JIAZHI" << "CHUZUJIAGE" << "SHEBEIZHUANGTAI" << "ZUIJINYICIJIECHUJIELU" << "SHEBEITUPIAN" << "BEIZHU";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(10);
	/*
	//����ÿ�еĿ��
	for (int i=0; i <= ui->tableWidget->rowCount(); i++)
		ui->tableWidget->setColumnWidth(i, 200);
		*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
