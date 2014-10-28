#include "lendwindow.h"
#include "ui_lendwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

lendwindow::lendwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::lendwindow)
{
	ui->setupUi(this);
}
lendwindow::~lendwindow()
{
	delete ui;
}

void lendwindow::on_ok_clicked()
{

}
void lendwindow::on_exit_clicked()
{

}