#ifndef _RETURNWINDOW_H
#define _RETURNWINDOW_H

#include <QtCore/QStringlist>
#include <QtWidgets/QDialog>
#include "db_layer.h"

namespace Ui {
	class returnwindow;
}

class returnwindow : public QDialog
{
	Q_OBJECT

public:
	explicit returnwindow(QWidget *parent = 0);
	~returnwindow();
	std::vector<LendRecord>li = Database::get().getLendRecordList(Database::STATE_ALL, nullptr, nullptr);
	private slots:
	void on_ok_clicked();
	void on_exit_clicked();

private:
	Ui::returnwindow *ui;
};

#endif 