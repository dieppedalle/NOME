//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include "TransformationNew.h"
#include <stdio.h>
#include <stdlib.h>

Rotate* createRotate(double *x, double *y, double *z, double *angle)
{
    Rotate * rotate = new Rotate();
    rotate->x = x;
    rotate->y = y;
    rotate->z = z;
    rotate->angle = angle;
    return rotate;
}

Reverse* createReverse()
{
    Reverse * reverse = new Reverse();
    return reverse;
}

Scale* createScale(double *x, double *y, double *z)
{
    Scale * scale = new Scale();
    scale->x = x;
    scale->y = y;
    scale->z = z;
    return scale;
}

Translate* createTranslate(double *x, double *y, double *z)
{
    Translate * translate = new Translate();
    translate->x = x;
    translate->y = y;
    translate->z = z;
    return translate;
}

void copyStateTransformation(TransformationNew * t, std::list<TransformationNew*> *transformations){
    if (dynamic_cast<Rotate*>(t)){
        Rotate* rotate = dynamic_cast<Rotate*>(t);

        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));
        double *angle = (double*) malloc(sizeof(double));

        *x = *rotate->x;
        *y = *rotate->y;
        *z = *rotate->z;
        *angle = *rotate->angle;

        Rotate* transformNew = createRotate(x, y, z, angle);
        transformations->push_back(transformNew);
    } else if (dynamic_cast<Reverse*>(t)){
        Reverse* reverse = dynamic_cast<Reverse*>(t);

        Reverse* transformNew = createReverse();
        transformations->push_back(transformNew);
    }
    else if (dynamic_cast<Scale*>(t)){
        Scale* scale = dynamic_cast<Scale*>(t);
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = *scale->x;
        *y = *scale->y;
        *z = *scale->z;

        Scale* transformNew = createScale(x, y, z);
        transformations->push_back(transformNew);

    }
    else if (dynamic_cast<Translate*>(t)){
        Translate* translate = dynamic_cast<Translate*>(t);
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = *translate->x;
        *y = *translate->y;
        *z = *translate->z;

        Translate* transformNew = createTranslate(x, y, z);
        transformations->push_back(transformNew);
    }


}
