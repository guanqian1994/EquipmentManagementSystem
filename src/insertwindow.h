#ifndef _INSERTWINDOW_H
#define _INSERTWINDOW_H

#include <QtWidgets/QDialog>
#include "db_layer.h"

namespace Ui {
	class insertwindow;
}

class insertwindow : public QDialog
{
	Q_OBJECT

public:
	explicit insertwindow(QWidget *parent = 0);
	~insertwindow();

	private slots:
	void on_openfile_clicked();
	void on_ok_clicked();
	void on_exit_clicked();

private:
	Ui::insertwindow *ui;
	EquipmentData e;
};

#endif 