#include "mainwindow.h"
#include "db_layer.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    try {
        Database database;
        MainWindow w;
        w.show();
        return a.exec();
    } catch (std::exception& e) {
        QMessageBox::information(NULL, "Error", e.what(), QMessageBox::Yes, QMessageBox::Yes);
    }
    return 0;
}
