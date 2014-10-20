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

private:
    Ui::MainWindow *ui;
	QStringList list;
};

#endif // MAINWINDOW_H
