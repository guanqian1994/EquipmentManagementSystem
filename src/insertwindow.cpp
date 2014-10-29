#include "insertwindow.h"
#include "ui_insertwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include "db_layer.h"

#include <QtCore/QString>
#include <QtWidgets/QFiledialog>
#include <QtCore/QBuffer>

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
	//定义相关的变量
	QString name = ui->lineEdit->text();
	//QString registration_date = ui->dateEdit->text();
	//QMessageBox::information(this, tr("123"),a, QMessageBox::Ok);
	QString description = ui->lineEdit_2->text();
	QString registrationOperator = ui->lineEdit_3->text();
	QString value = ui->lineEdit_4->text();
	QString lendPrice = ui->lineEdit_5->text();
	QString remark = ui->textEdit->toPlainText();
	Database::get().registration({ 0, name, description, "2010-2-2", registrationOperator, value.toUInt(), lendPrice.toUInt(), false, 0, QImage(), remark });
	/*if (Database::get().registration==false)
		QMessageBox::information(this, tr("Error"), tr("插入失败!"), QMessageBox::Ok);*/

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
	////save the pic to database
	//QByteArray bytes;
	//QBuffer buffer(&bytes);
	//buffer.open(QIODevice::WriteOnly);
	//ui->labelPic->pixmap()->save(&buffer, "JPG");
	//QByteArray data;
	//QString path = strImage;
	//QFile*file = new QFile(path);//the filename is 2jinzhi
	//file->open(QIODevice::ReadOnly);
	//data = file->readAll();
	//file->close();
	//QVariant var(data);

}