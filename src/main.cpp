#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if(argc == 2)
    {
        w.cargaInit(argv[1]);
    }
    else
    {
        w.cargaInit("");
    }

    //w.cargaInit("C:\\Documents and Settings\\Administrador\\Mis documentos\\ini.html");
    w.show();
    return a.exec();
}
