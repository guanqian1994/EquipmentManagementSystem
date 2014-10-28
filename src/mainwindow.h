#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/Qstringlist>

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
	void on_lend_clicked();
	void on_return_clicked();
	void on_exit_clicked();
	void on_insert_clicked();


private:
    Ui::MainWindow *ui;
	QStringList list;
};

#endif // MAINWINDOW_H
