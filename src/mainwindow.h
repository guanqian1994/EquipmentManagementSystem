#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/Qstringlist>

#define BUFF_SIZE 24

#pragma execution_character_set("utf-8")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	private slots:
	void on_all_clicked();
	void on_record_clicked();
	void on_manage_clicked();
	void on_lend_clicked();
	void on_return_2_clicked();
	void on_exit_clicked();
	void on_insert_clicked();
	void doubleclicked();


private:
    Ui::MainWindow *ui;
	QStringList list;
    char _buff[BUFF_SIZE];
	
};

#endif // MAINWINDOW_H
