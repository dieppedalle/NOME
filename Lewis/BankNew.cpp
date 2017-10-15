//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "BankNew.h"
#include "Data.h"
#include "MySliderNew.h"
#include "SliderWindow.h"
#include "SliderNew.h"

//Instantiation
BankNew* createBank(){
    BankNew* b0 = new BankNew();
    //i0->mesh = m0;
    return b0;
}

SetNew* createSet(std::string name, double value, double start, double end, double stepSize){
    SetNew* s0 = new SetNew();
    s0->name = name;
    s0->value = value;
    s0->start = start;
    s0->end = end;
    s0->stepSize = stepSize;
    return s0;
}

bool BankNew::draw()
{
    //SliderWindow *window = new SliderWindow(this);
    //window->show();

    QWidget *window = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(window);
    QLabel* label = new QLabel(this->name.c_str());
    layout->addWidget(label);
    for(auto s : sets) {
        layout -> addLayout(new SliderNew(s));
    }
    window->setLayout(layout);
    window->show();
    /*MySliderNew();

    QWidget *window = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QString str = QString::fromUtf8(name.c_str());
    mainLayout->addWidget(new QLabel(str));
    window->setLayout(mainLayout);
    window->show();

    for(auto s : sets) {
        QString str = QString::fromUtf8(s->name.c_str());
        //mainLayout->addWidget(new QLabel(str));

        mainLayout -> addWidget(new QLabel(str + QString(" : ") + QString::number(s->value)));

        QSlider* slider = new QSlider(Qt::Horizontal);
        mainLayout -> addWidget(slider);
        slider -> setMinimum(s->start);
        slider -> setMaximum(s->end);
        slider -> setValue(s->value);
        slider -> setSingleStep(s->stepSize);


        window->setLayout(mainLayout);
        window->show();
    }*/
}

int testFunction(int hello){
    std::cout << "HELLO" << std::endl;
}
