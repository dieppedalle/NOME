#include "MySliderNew.h"
#include "parameter.h"
#include "Data.h"

MySliderNew::MySliderNew()
{
    generalSetup();
}

MySliderNew::MySliderNew(Parameter *param)
{
    generalSetup();
}

void MySliderNew::generalSetup()
{
    QWidget *window = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    window->setLayout(mainLayout);
    mainLayout -> addWidget(currValue = new QLabel(("HELLO") + QString(" : ") +QString::number(1)));
    QHBoxLayout *sliderLayout;
    mainLayout -> addLayout(sliderLayout = new QHBoxLayout);
    sliderLayout -> addWidget(new QLabel(QString::number(0)));
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    sliderLayout -> addWidget(slider);
    slider -> setMinimum(0);
    slider -> setMaximum(int((20)));
    slider -> setValue(int((10)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    sliderLayout -> addWidget(new QLabel(QString::number(20)));
    window->show();

    std::cout << "TEST" << std::endl;
}


void MySliderNew::changeValue(int newValue)
{
    currValue-> setText(("HELLO") + QString(" : ") +QString::number(4));
    std::cout << "edges->size()" << std::endl;
    //emit paramValueChanged(1);
}
