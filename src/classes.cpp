#include <QProcess>
#include <QMessageBox>
#include "classes.h"
#include <stdio.h>
#include <QFile>
#include <QWebFrame>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
//#include <QTimer>
/*******************************RUN**********************************************/
Gcc::Gcc( QObject *parent )
    : QObject( parent )
{
}
void Gcc::iniciaGcc(QWebView *view)
    {
        QWebPage *page = view->page();
        frame = page->mainFrame();
        insertaGcc();
        connect( frame, SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(insertaGcc()));
    }
void Gcc::insertaGcc()
    {
        frame->addToJavaScriptWindowObject( QString("Gcc"), this );//Original
        frame->addToJavaScriptWindowObject( QString("gcc"), this );//alternativo
    }
QString Gcc::exec(QString cmd, bool wait) const
    {
    int result;
    /*QStringList app = cmd.split(' ');

    if(QFile::exists(app[0]))
        {*/
    QProcess proc(0);

    if(wait)
     {
          proc.start(cmd);
          proc.waitForFinished(-1);
          result = proc.exitCode();
    }
  else
    {
        QEventLoop waitLoop;
        connect(&proc, SIGNAL(finished(int, QProcess::ExitStatus)),&waitLoop, SLOT(quit()));
        proc.start(cmd);
        waitLoop.exec();
        result = -1;
    }
            //proc.close();
       return QString("%1").arg(result);
        /*}
    else
        {
            //frame->evaluateJavaScript("console.log('No se encontro el comando '"+ cmd +")").toString();
            QMessageBox::critical(wnd,wnd->windowTitle(),QString("No se encontro el comando ->(%1)").arg(app[0]));
            return QString("-1");
        }*/
    }
int Gcc::window(int w, int h) const
{
    wnd->resize(w,h);
    //QMessageBox::critical(wnd,wnd->windowTitle(),QString("parametros w = %1 h = %2").arg(w));
    return 0;
}

int Gcc::windowPos(int x, int y) const
{
    wnd->move(x,y);
    return 0;
}

int Gcc::windowFull() const
{
    wnd->showFullScreen();
    return 0;
}
int Gcc::windowMax() const
{
    wnd->showMaximized();
    return 0;
}
int Gcc::windowMin() const
{
    wnd->showMinimized();
    return 0;
}

void Gcc::exit() const
{
    emit wnd->close();
}

void Gcc::holdBtnmax() const
{
   wnd->setFixedSize(wnd->width(), wnd->height());
}

QString Gcc::readFile(QString fileName) const
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
            QByteArray fileData = file.readAll();
            file.close();
            return QString(fileData);
        }
        else
        {
          //QMessageBox::critical(wnd,wnd->windowTitle(),QString("No se encontro el comando ->(%1)").arg(app[0]));
            return QString("-1");
        }
}
int Gcc::writeFile(QString fileName, QByteArray content) const
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
            file.write(content);
            file.close();
            return 0;
        }
        else
        {
          //QMessageBox::critical(wnd,wnd->windowTitle(),QString("No se encontro el comando ->(%1)").arg(app[0]));
            return -1;
        }
}
QString Gcc::version() const
{
    return Version;
}
QString Gcc::status() const
{
    return Status;
}
void Gcc::iconChange(QString iconName) const
{
    QIcon icn;
    icn.addFile(QString::fromUtf8(iconName.toStdString().c_str()), QSize(), QIcon::Normal, QIcon::Off);
    wnd->setWindowIcon(icn);
    wnd->setIconSize(QSize(32, 32));
}
QString Gcc::appPath() const
{
#ifdef _WIN32
    return QFileInfo(QCoreApplication::applicationFilePath()).path().replace("/","\\");
#else
    return QFileInfo(QCoreApplication::applicationFilePath()).path();
#endif

}
QString Gcc::appName() const
{
    return QFileInfo(QCoreApplication::applicationFilePath()).fileName();
}
int Gcc::information(QString texto) const
{
    int resp = 0;
    if(QMessageBox::information(wnd,wnd->windowTitle(),texto) ==  QMessageBox::Ok)
        resp = 3;
    return (resp);

}
int Gcc::warning(QString texto) const
{
    int resp = 0;
    if(QMessageBox::warning(wnd,wnd->windowTitle(),texto) ==  QMessageBox::Ok)
        resp = 3;
    return (resp);

}
int Gcc::critical(QString texto) const
{
    int resp = 0;
    if(QMessageBox::critical(wnd,wnd->windowTitle(),texto) ==  QMessageBox::Ok)
        resp = 3;
    return (resp);

}
int Gcc::question(QString texto) const
{
    int resp = 0;
    if(QMessageBox::question(wnd,wnd->windowTitle(),texto,QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        resp = 1;
    return (resp);
}
QString Gcc::_type() const
{
    return sType;
}
int Gcc::createDir(QString dirName) const
{
    QDir dir;//(dirName);
    if(!dir.exists(dirName))
    {
        dir.mkpath(dirName);
        return 0;
    }
    else
    {
        return -1;
    }
}
QStringList Gcc::infoListDir(QString dirName, int _type) const
{
    QDir dir(dirName);
    QStringList result;
    foreach(QFileInfo item, dir.entryInfoList() )
    {
        if(_type == 0 && item.isDir())//opcion 0 solo directorios
        {
            #ifdef _WIN32
                result.append(item.absoluteFilePath().replace("/","\\"));
            #else
               result.append(item.absoluteFilePath());
            #endif
        }
        if(_type == 1 && item.isFile())//opcion 1 solo archivos con ruta absoluta
        {
            #ifdef _WIN32
                result << item.absoluteFilePath().replace("/","\\");
            #else
               result << item.absoluteFilePath();
            #endif
        }
        if(_type == 3 && item.isFile())//opcion 3 solo archivos nombres
        {
            #ifdef _WIN32
                result << item.fileName().replace("/","\\");
            #else
               result << item.fileName();
            #endif
        }
    }
    return result;
    /*/QString obj = "{", objDir = "dirs:[", objFile = "files:[";
    bool iniDir = true, iniFile = true;
    if(objInfodir == "")
        return -1;

    foreach(QFileInfo item, dir.entryInfoList() )
    {
        if(item.isDir())
        {
            if(iniDir)
              {
                #ifdef _WIN32
                    objDir = objDir + '"' +item.absoluteFilePath().replace("/","\\") + '"';
                #else
                    objDir = objDir + '"' +item.absoluteFilePath() + '"';
                #endif

                iniDir = false;
              }
            else
            {
                objDir = objDir + ',' + '"' +item.absoluteFilePath() + '"';
            }

        }
        if(item.isFile())
        {
            if(iniFile)
              {
                objFile = objFile + '"' + item.absoluteFilePath() + '"';
                iniFile = false;
              }
            else
            {
                objFile = objFile + ',' + '"' + item.absoluteFilePath() + '"';
            }
        }

    }
    objDir = objDir + ']';
    objFile = objFile + ']';
    obj = obj + objDir + ',' + objFile + "};";
    frame->evaluateJavaScript(objInfodir + " = " + obj);//.toString();
    //
    return 0;*/
}
int Gcc::buildingCode(QString inputFile, QString outputFile) const
{
    QFile infile(inputFile);
    QFile outfile(outputFile);
    if(infile.open(QIODevice::ReadOnly))
    {
        if(outfile.open(QIODevice::WriteOnly))
        {
            QByteArray uncompressed_data = infile.readAll();
            QByteArray compressed_data = qCompress(uncompressed_data, 9);
            outfile.write(compressed_data);
            infile.close();
            outfile.close();
            return 0;
        }
        else
        {
            infile.close();
            return -2;
        }
    }
    else
    {
        return -1;
    }
}
QString Gcc::shell(QByteArray cmd) const
  {
    QByteArray result;
    QProcess sh;
    #ifdef _WIN32
        sh.start("cmd /c "/*,QStringList() << "/c" <<*/+ cmd);
    #else
        sh.start("sh",QStringList() << "-c" << cmd);
    #endif
    //sh.write(cmd);
    //sh.closeWriteChannel();
    sh.waitForFinished();
    result = sh.readAll();
    sh.close();
    return QString(result);
  }

void Gcc::newWindow(QString content, bool wait) const
{
    QProcess proc(0);
    QString cmd;

    #ifdef _WIN32
        cmd = QFileInfo(QCoreApplication::applicationFilePath()).absoluteFilePath().replace("/","\\");
    #else
        cmd = QFileInfo(QCoreApplication::applicationFilePath()).absoluteFilePath();
    #endif

    cmd = '"' + cmd + '"' + ' ' + content;

    if(wait)
     {
          proc.start(cmd);
          proc.waitForFinished(-1);
    }
  else
    {
        QEventLoop waitLoop;
        connect(&proc, SIGNAL(finished(int, QProcess::ExitStatus)),&waitLoop, SLOT(quit()));
        proc.start(cmd);
        waitLoop.exec();
    }
}
/*void Gcc::hideW() const
{
     QTimer::singleShot(1, wnd, SLOT(hide()));
}

void Gcc::showW() const
{
    QTimer::singleShot(1, wnd, SLOT(show()));
}*/
