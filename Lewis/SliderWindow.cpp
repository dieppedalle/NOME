//SliderWindow.cpp File

#include "SliderWindow.h"
#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "Data.h"

SliderWindow::SliderWindow(BankNew* bank)
{
    setWindowTitle(QString::fromUtf8(bank->name.c_str()));
    //setFixedSize(250,250);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    label = new QLabel("rib.n: "+ QString::number(0));

    layout->addWidget(label);
    QHBoxLayout *sliderLayout;
    layout -> addLayout(sliderLayout = new QHBoxLayout);
    sliderLayout -> addWidget(new QLabel(QString::number(0)));
    //Initialize Slider and Label here
    slider = new QSlider(Qt::Horizontal);
    slider -> setPageStep(1);
    slider -> setMinimum(0);
    slider -> setMaximum(200);
    slider -> setValue(0);
    std::cout << slider -> tickInterval() << std::endl;


    sliderLayout->addWidget(slider);
    sliderLayout -> addWidget(new QLabel(QString::number(200)));

    setCentralWidget(centralWidget);

    //connect valueChanged(int) signal of QSlider sliderValueChanged(int)
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
};

void SliderWindow::sliderValueChanged(int value)
{
    label->setText("rib.n: "+ QString::number(value) );
};


