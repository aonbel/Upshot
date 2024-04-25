#ifndef MYMATH_H
#define MYMATH_H

#include <QtMath>
#include <QtCore>
#include <vector>
#include <algorithm>

#include "edge.h"

const float PI = M_PI;
// ANY EPS's THAT LESS THAN 10 ARE NOT GOOD
const float EPS = 10;

float distanceBetweenQPoints(QPointF first, QPointF second);

float vectorLength(QPointF vector);

float vectorAngle(QPointF vector);

bool isEqual(float first, float second);

bool isEqual(QPointF first, QPointF second);

float angleBetweenEdges(Edge first, Edge second);

QPointF rotateVector(QPointF vector, float angle);

#endif // MYMATH_H
