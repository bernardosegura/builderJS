#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classes.h"
#include <QFile>
#include <QWebFrame>
#include <QFileInfo>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Gcc *gcc = new Gcc(ui->Contenido);
    gcc->wnd = this;
    gcc->iniciaGcc(ui->Contenido);

    if(sType == QString("Develop"))
    {
        /////////////////////////para el Decelopers////////////////////////////////////////////
        ui->Contenido->settings()->globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,true);
        //////////////////////////Click derecho Inspect :)/////////////////////////////////////
    }
    else
    {
        ////////////////////////////Para quitar el menu contextual RunTime//////////////////////
        ui->Contenido->setContextMenuPolicy(Qt::NoContextMenu);
        ////////////////////////////No context menu is allowed if you don't need it/////////////
    }
}
void MainWindow::resizeEvent ( QResizeEvent *event )
 {
    //ui->listWidget->setGeometry(QRect(0,0,this->size().width(),this->size().height()));
    ui->Contenido->setGeometry(QRect(0,0,this->size().width(),this->size().height()));
 }

void MainWindow::cargaInit(QString code)
{
    QString path = "";
    //Se comento para mandar como parametro la url de donde esta el archivo
    //y pueda partir de ahi para cargar cualquier archivo del html.
    //no fue necesario hacer la conversion para windows ya q si la interpreto
    //de manera interna solo cuando se exporta si se tiene q convertir las diagonales
    /*#ifdef _WIN32
        path = QFileInfo(QCoreApplication::applicationFilePath()).path().replace("/","\\");
        path = path + '\\';
    #else*/
        path = QFileInfo(QCoreApplication::applicationFilePath()).path();
        path = path + '/';
    /*#endif*/

    if(sType == QString("Develop"))
    {
        if(code == "")
        {
            code = path + "index.html";
        }
        else
        {
          code = path + code;
        }
       //QMessageBox::critical(this,this->windowTitle(),code);
        QFile file;
        if (file.exists(code)) {
                ui->Contenido->setUrl("file://"+code);//validar si funciona en windows
            }
            else
            {
              this->window()->setWindowTitle(QString("Error No found: " + code));
              //Mandar mensaje en el RunTime
            }
    }
    else
    {
        if(code == "")
        {
            code = path + "start.dat";//codificar dicho archivo con comprecion
        }
        else
        {
            code = code.toLower();
            code = code.replace(".html",".dat");
            code = path + code;
        }

        QFile file(code);
        if (file.open(QIODevice::ReadOnly)){
                QByteArray fileData = file.readAll();
                file.close();
                 QByteArray htmlData = qUncompress(fileData);
                //ui->Contenido->setHtml(QString(fileData).replace("{_PATH}",path));
                ui->Contenido->setHtml(QString(htmlData),path);
                //ui->Contenido->page()->mainFrame()->evaluateJavaScript("<script>function mensaje(){alert('Hola');}</script>");
            }
            else
            {
              QMessageBox::critical(this,this->windowTitle(),QString("Error No found: " + code));
              QTimer::singleShot(1,this,SLOT(close()));
            }
    }

}

/*void MainWindow::cambiarIcono()
{
    //ui->Contenido->page()->mainFrame()->evaluateJavaScript("<script>alert('Hola');</script>");
    this->setWindowIcon(ui->Contenido->icon());
}*/
/*bool MainWindow::eventFilter(QObject *obj, QEvent *event) {

    if (event->type() == QEvent::Close && this->btnClose == false) {
        event->ignore();
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}*/
MainWindow::~MainWindow()
{
    delete ui;
}
