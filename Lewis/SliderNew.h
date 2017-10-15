//SliderWindow.h File

#ifndef SLIDERNEW_H
#define SLIDERNEW_H

#include <QtGui>
#include "BankNew.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

class SliderNew: public QVBoxLayout
{
  Q_OBJECT
  public:
    SliderNew(SetNew* set);
    ~ SliderNew(){};

   public slots:
    void sliderValueChanged(int value);

  public:
  SetNew* set;
  QSlider* slider;
  QLabel* label;
};

#endif
