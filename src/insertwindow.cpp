#include "insertwindow.h"
#include "ui_insertwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"

#include <QtCore/QString>
#include <QtWidgets/QFiledialog>
#include <QtCore/QBuffer>
#include <QtWidgets/QDatetimeedit>

insertwindow::insertwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::insertwindow)
{
	ui->setupUi(this);
	ui->dateEdit->setDateTime(QDateTime::currentDateTime());
	ui->dateEdit->setReadOnly(true);
	ui->lineEdit_3->setText("默认当前用户");
	ui->lineEdit_3->setFocus();
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
	//QString registrationOperator = ui->lineEdit_3->text();
	QString value = ui->lineEdit_4->text();
	QString lendPrice = ui->lineEdit_5->text();
	QString remark = ui->textEdit->toPlainText();
	e._id = 0; 
	e._description = description; 
	//e._registrationOperator = registrationOperator; 
	e._name = name;
	e._registrationDate = "2010-2-2";
	e._value = value.toFloat();
	e._lendPrice = lendPrice.toFloat();
	e._isLending = false;
	e._recentLendRecord = 0;
	e._remark = remark;
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定采购？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().registration(e))
			QMessageBox::information(this, tr("提示"), tr("采购成功!"), QMessageBox::Ok);
	}
}
void insertwindow::on_exit_clicked()
{
	this->close();
}
void insertwindow::on_openfile_clicked()
{
	QString g_strCurrentDir;
	QString strImage = QFileDialog::getOpenFileName(this, tr("请选择一张图片"), g_strCurrentDir,"Image Format(*.png *.jpg *.bmp *.gif)");
	if (strImage.isNull())
	{
	return;
	}
	g_strCurrentDir = QDir(strImage).absolutePath();
	ui->labelPic->setPixmap(QPixmap(strImage).scaled(ui->labelPic->size()));
	e._image = QImage(strImage);
}