//SliderWindow.h File

#ifndef SLIDERSUBDIVISIONNEW_H
#define SLIDERSUBDIVISIONNEW_H

#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "nomeglwidget.h"

class SliderSubdivisionNew: public QVBoxLayout
{
  Q_OBJECT
  public:
    SliderSubdivisionNew(SubdivisionNew* subdivision, SlideGLWidget * canvas);
    ~ SliderSubdivisionNew(){};

   public slots:
    void sliderValueChanged(int value);

  public:
  SubdivisionNew* subdivision;
  QSlider* slider;
  QLabel* label;
  SlideGLWidget * canvas;
};

#endif
