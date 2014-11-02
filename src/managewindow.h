#ifndef _MANAGEWINDOW_H
#define _MANAGEWINDOW_H

#define BUFF_SIZE 24
#define snprintf _snprintf

#include <QtWidgets/QDialog>
#include "QtCore/QList"
#include "QtWidgets/QTablewidget"

namespace Ui {
	class managewindow;
}

class managewindow : public QDialog
{
	Q_OBJECT

public:
	explicit managewindow(QWidget *parent = 0);
	~managewindow();

	private slots:
	void on_update_clicked();
	void on_delete_2_clicked();
	void on_exit_clicked();

private:
	Ui::managewindow *ui;
	QStringList list;
	char _buff[BUFF_SIZE];
	char _buff2[BUFF_SIZE];
	char _buff3[BUFF_SIZE];
};

#endif 