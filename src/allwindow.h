#ifndef _ALLWINDOW_H
#define _ALLWINDOW_H

#define BUFF_SIZE 24
#define snprintf _snprintf
#include <QtWidgets/QDialog>
#include "db_layer.h"
namespace Ui {
	class allwindow;
}

class allwindow : public QDialog
{
	Q_OBJECT

public:
	explicit allwindow(QWidget *parent = 0);
	void sendValue(EquipmentData& equipment);
	~allwindow();
	private slots:
	void on_delete_2_clicked();
	void on_exit_clicked();
	void on_update_clicked();

private:
	Ui::allwindow *ui;
	QStringList list;
	char _buff[BUFF_SIZE];
};

#endif 