
#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"
#include "tableWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Window window;
    //window.show();
    tableWindow *table = new tableWindow;
    table->show();
    return app.exec();
}
