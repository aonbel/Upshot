#ifndef MYMATH_H
#define MYMATH_H

#include <QtMath>
#include <QtCore>
#include <algorithm>
#include <queue>

const float PI = M_PI;
const float EPS = 0.1;
const float FLOAT_MAX_VALUE = 1e9;

float vectorLength(QPointF vector);

float vectorAngle(QPointF vector);

bool isEqual(float first, float second, float eps = EPS);

bool isEqual(QPointF first, QPointF second, float eps = EPS);

float angleBetweenVectors(QPointF first, QPointF second);

QPointF rotateVector(QPointF vector, float angle);

float scalarMultiplicationVectors(QPointF first, QPointF second);

#endif // MYMATH_H
