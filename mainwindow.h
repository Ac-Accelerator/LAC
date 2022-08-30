#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculate.h"
#include "editor.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTimerEvent>
#include <fstream>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Size_check *check_window;
    MainWindow(QWidget *parent = nullptr);
    virtual void timerEvent(QTimerEvent *);
    ~MainWindow();

private:
    void compute();
    void load();
    void write();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
