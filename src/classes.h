#ifndef CLASSES_H
#define CLASSES_H

#include <QWebView>
#include <QWebFrame>
#include <QMainWindow>
#include <QIcon>

#define Version "1.482"
#define Status "Alpha"
#define sType "Develop"
//#define sType "Construct"
//#define sType "Runtime"

class Gcc : public QObject
{
Q_OBJECT
private:
     QWebFrame *frame;
public:
     QMainWindow *wnd;
public:
     Gcc(QObject*);
    void iniciaGcc(QWebView*);
    Q_INVOKABLE QString exec(QString cmd, bool wait) const;
    Q_INVOKABLE int window(int w,int h) const;
    Q_INVOKABLE int windowPos(int x,int y) const;
    Q_INVOKABLE int windowFull() const;
    Q_INVOKABLE int windowMax() const;
    Q_INVOKABLE int windowMin() const;
    Q_INVOKABLE void exit() const;
    Q_INVOKABLE void holdBtnmax() const;
    Q_INVOKABLE QString readFile(QString fileName) const;
    Q_INVOKABLE int writeFile(QString fileName, QByteArray content) const;
    Q_INVOKABLE QString version() const;
    Q_INVOKABLE QString status() const;
    Q_INVOKABLE void iconChange(QString iconName) const;//32 * 32
    Q_INVOKABLE QString appPath() const;
    Q_INVOKABLE QString appName() const;
    Q_INVOKABLE int information(QString texto) const;
    Q_INVOKABLE int warning(QString texto) const;
    Q_INVOKABLE int critical(QString texto) const;
    Q_INVOKABLE int question(QString texto) const;
    Q_INVOKABLE QString _type() const;
    Q_INVOKABLE int createDir(QString dirName) const;
    Q_INVOKABLE QStringList infoListDir(QString dirName, int _type) const;
    Q_INVOKABLE int buildingCode(QString inputFile, QString outputFile) const;//comprime el texto introducido
    Q_INVOKABLE QString shell(QByteArray cmd) const;
    Q_INVOKABLE void newWindow(QString content, bool wait) const;
    /*Q_INVOKABLE void hideW() const;
    Q_INVOKABLE void showW() const;*/
private slots:
    void insertaGcc();
};
#endif //CLASSES_H
