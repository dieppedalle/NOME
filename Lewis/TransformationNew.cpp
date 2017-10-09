//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include "TransformationNew.h"

Rotate* createRotate(double x, double y, double z, double angle)
{
    Rotate * rotate = new Rotate();
    rotate->x = x;
    rotate->y = y;
    rotate->z = z;
    rotate->angle = angle;
    return rotate;
}

Scale* createScale(double x, double y, double z)
{
    Scale * scale = new Scale();
    scale->x = x;
    scale->y = y;
    scale->z = z;
    return scale;
}

Translate* createTranslate(double x, double y, double z)
{
    Translate * translate = new Translate();
    translate->x = x;
    translate->y = y;
    translate->z = z;
    return translate;
}
