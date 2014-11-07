#ifndef _RECENTWINDOW_H
#define _RECENTWINDOW_H

#include <QtCore/QStringlist>
#include <QtWidgets/QDialog>

namespace Ui {
	class recentwindow;
}

class recentwindow : public QDialog
{
	Q_OBJECT

public:
	explicit recentwindow(QWidget *parent = 0);
	~recentwindow();

	private slots:
	void on_ok_clicked();
	void on_exit_clicked();

private:
	Ui::recentwindow *ui;
	QStringList list;
};

#endif 