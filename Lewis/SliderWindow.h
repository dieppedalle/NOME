//SliderWindow.h File

#ifndef SLIDERWINDOW_H
#define SLIDERWINDOW_H

#include <QtGui>
#include "BankNew.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

class SliderWindow: public QMainWindow
{
  Q_OBJECT
  public:
    SliderWindow(BankNew* bank);
    ~ SliderWindow(){};

   public slots:
    void sliderValueChanged(int value);

  public:
  QSlider* slider;
  QLabel* label;
};

#endif
