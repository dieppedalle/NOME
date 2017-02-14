/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "mainwindow.h"
#include "nomeglwidget.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    cout << "Welcome to NOME!" << endl;


    QApplication a(argc, argv);
    //SlideGLWidget s;
    //s.show();
    MainWindow window;
    window.setGeometry(200,200,400,100);
    window.show();

    return a.exec();
}
