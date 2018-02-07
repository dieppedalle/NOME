#ifndef MYSLIDERNEW_H
#define MYSLIDERNEW_H

#include <QWidget>
#include "parameter.h"
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MySliderNew : public QWidget
{
    Q_OBJECT

public:
    MySliderNew();
    MySliderNew(Parameter *param);
    void generalSetup();
    QSlider *slider;
    QLabel *currValue;

    std::string name;
    double value;
    double start;
    double end;
    double stepSize;
public slots:
    void changeValue(int);
};

#endif // MYSLIDER_H
