#ifndef _RETURNWINDOW_H
#define _RETURNWINDOW_H

#include <QtCore/QStringlist>
#include <QtWidgets/QDialog>
#define BUFF_SIZE 24
namespace Ui {
	class returnwindow;
}

class returnwindow : public QDialog
{
	Q_OBJECT

public:
	explicit returnwindow(QWidget *parent = 0);
	~returnwindow();

	private slots:
	void on_ok_clicked();
	void on_exit_clicked();

private:
	Ui::returnwindow *ui;
	QStringList list;
	char _buff[BUFF_SIZE];
};

#endif 