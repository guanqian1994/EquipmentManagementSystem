#include "insertwindow.h"
#include "ui_insertwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

#include<QtCore\qstring.h>
#include<QtWidgets\qfiledialog.h>

insertwindow::insertwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::insertwindow)
{
	ui->setupUi(this);
	
		
}
insertwindow::~insertwindow()
{
	delete ui;
}

void insertwindow::on_ok_clicked()
{

}
void insertwindow::on_exit_clicked()
{
	this->close();
}
void insertwindow::on_openfile_clicked()
{
	QString g_strCurrentDir;
	QString strImage = QFileDialog::getOpenFileName(this, "Please Select image file", g_strCurrentDir,"Image Format(*.png *.jpg *.bmp *.gif)");
	if (strImage.isNull())
	{
	return;
	}
	g_strCurrentDir = QDir(strImage).absolutePath();
	ui->labelPic->setPixmap(QPixmap(strImage).scaled(ui->labelPic->size()));
}