#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent ( QResizeEvent *event );
    void cargaInit(QString code);

/*public slots:
    void cambiarIcono();*/

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
