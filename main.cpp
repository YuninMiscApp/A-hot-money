#include "mainwindow.h"
#include <QApplication>

#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.show();
    return app.exec();
}
