#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/Qtextcodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	//TableWiget
	ui->tableWidget->setColumnCount(10);
	list << "呵呵" << "SHEBEIMIAOSHU" << "DENGJIRIQI" << "DENGJICAOZUOYUAN" << "JIAZHI" << "CHUZUJIAGE" << "SHEBEIZHUANGTAI" << "ZUIJINYICIJIECHUJIELU" << "SHEBEITUPIAN" << "BEIZHU";
	ui->tableWidget->setHorizontalHeaderLabels(list);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}
