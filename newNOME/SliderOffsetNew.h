//SliderWindow.h File

#ifndef SLIDEROFFSETNEW_H
#define SLIDEROFFSETNEW_H

#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "nomeglwidget.h"

class SliderOffsetNew: public QVBoxLayout
{
  Q_OBJECT
  public:
    SliderOffsetNew(OffsetNew* offset, SlideGLWidget * canvas);
    ~ SliderOffsetNew(){};

   public slots:
    void sliderValueChanged(int value);

  public:
  OffsetNew* offset;
  QSlider* slider;
  QLabel* label;
  SlideGLWidget * canvas;
};

#endif
