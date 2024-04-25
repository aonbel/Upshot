#ifndef MYMATH_H
#define MYMATH_H

#include <QtMath>
#include <QtCore>
#include <vector>
#include <algorithm>

#include "edge.h"

const float PI = 3.14159;
// ANY EPS's THAT LESS THAN 1 ARE NOT GOOD
const float EPS = 20;

float distanceBetweenQPoints(QPointF first, QPointF second);

float vectorLength(QPointF vector);

float vectorAngle(QPointF vector);

bool isEqual(float first, float second);

bool isEqual(QPointF first, QPointF second);

float angleBetweenEdges(Edge first, Edge second);

#endif // MYMATH_H
