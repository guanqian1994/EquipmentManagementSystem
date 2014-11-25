#include "mainwindow.h"
#include "loginwindow.h"
#include "db_layer.h"

#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#ifdef _MSC_VER
#   pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        Database database;
        loginwindow l;
        l.show();
        return a.exec();
    } catch (std::exception& e) {
        QMessageBox::information(NULL, "Error", e.what(), QMessageBox::Yes, QMessageBox::Yes);
    }
    return 0;
}
