#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "node.h"
#include <string>
#include <QtCharts/QChartView>         // Widget used to display charts
#include <QtCharts/QPieSeries>         // Used to make Pie Charts
#include <QtCharts/QPieSlice>
#include<sstream>
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <iostream>
#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QStringList>
#include <QString>
#include <QtGui>
#include <QtCore>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QLabel>
#include <stdio.h>
#include <sys/statvfs.h>


QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(vector<node>,string ,QWidget *parent = nullptr);
    ~MainWindow();
    vector<node> temp;
    int NDirectoriesShown=0;
    int is_regular_file(const char *path);
    string ParentDirectories;
    //
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

