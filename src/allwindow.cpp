#include "allwindow.h"
#include "ui_allwindow.h"
#include "QtWidgets/QMessagebox"
#include "mainwindow.h"
#include <QtWidgets/QFiledialog>

allwindow::allwindow(QWidget *parent) :
QDialog(parent),
ui(new Ui::allwindow)
{
	ui->setupUi(this);
	
}
allwindow::~allwindow()
{
	delete ui;
}

void allwindow::on_update_clicked()
{
	QString name = ui->name->text();
	QString description = ui->description->text();
	QString people = ui->people->text();
	QString value = ui->value->text();
	QString price = ui->price->text();
	QString remark = ui->remark->toPlainText();
	QString time = ui->date->text();
	QString Id = ui->id->text();
	e._id = Id.toUInt();
	e._description = description;
	e._registrationOperator = people; 
	e._name = name;
	e._registrationDate =time;
	e._value = value.toFloat();
	e._lendPrice = price.toFloat();
	e._recentLendRecord = 0;
	e._remark = remark;
	//snprintf(_buff, BUFF_SIZE, Id);
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定修改？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().updateEquipment(e))
			QMessageBox::information(this, tr("提示"), tr("修改成功!"), QMessageBox::Ok);
	}
	
}
void allwindow::on_exit_clicked()
{
	this->close();
}
void allwindow::on_delete_2_clicked()
{
	QString id = ui->id->text();
	QMessageBox msg(QMessageBox::NoIcon, tr("提示"), tr("确定删除？"), QMessageBox::Ok | QMessageBox::No, NULL);
	if (msg.exec() == QMessageBox::Ok)
	{
		if (Database::get().deleteEquipment(id.toUInt()))
			QMessageBox::information(this, tr("提示"), tr("删除成功!"), QMessageBox::Ok);
	}
}
void allwindow::on_update_pic_clicked()
{
	QString g_strCurrentDir;
	QString strImage = QFileDialog::getOpenFileName(this, "Please Select image file", g_strCurrentDir, "Image Format(*.png *.jpg *.bmp *.gif)");
	if (strImage.isNull())
	{
		return;
	}
	g_strCurrentDir = QDir(strImage).absolutePath();
	ui->pic->setPixmap(QPixmap(strImage).scaled(ui->pic->size()));
	e._image = QImage(strImage);
}
void allwindow::sendValue(EquipmentData& equipment)
{
    SNPRINTF(_buff, BUFF_SIZE, "%d", equipment._id);
	ui->id->setText(_buff);
	ui->name->setText(equipment._name);
	ui->description->setText(equipment._description);
	ui->date->setText(equipment._registrationDate);
	ui->people->setText(equipment._registrationOperator);
    SNPRINTF(_buff, BUFF_SIZE, "%.2f", equipment._value);
	ui->value->setText(_buff);
    SNPRINTF(_buff, BUFF_SIZE, "%.2f", equipment._lendPrice);
	ui->price->setText(_buff);
	
	ui->pic->setPixmap(QPixmap::fromImage(equipment._image).scaled(ui->pic->size()));
	ui->pic->setVisible(true);
	ui->islend->setText(equipment._isLending?"借出中":"尚未借出");
	ui->remark->setText(equipment._remark);
}