#include "returnwindow.h"
#include "ui_returnwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

returnwindow::returnwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::returnwindow)
{
	ui->setupUi(this);
}
returnwindow::~returnwindow()
{
	delete ui;
}

void returnwindow::on_ok_clicked()
{

}
void returnwindow::on_exit_clicked()
{

}
