#ifndef MYMATH_H
#define MYMATH_H

#include <QtMath>
#include <QtCore>
#include <algorithm>
#include <queue>

#include "edge.h"

const float PI = M_PI;
// ANY EPS's THAT LESS THAN 10 ARE NOT GOOD
const float EPS = 10;
const float FLOAT_MAX_VALUE = 1e9;
const QPointF DEF_QPOINTF(FLOAT_MAX_VALUE, FLOAT_MAX_VALUE);

inline bool operator<(const QPointF &p1, const QPointF &p2)
{
    return p1.x() * FLOAT_MAX_VALUE + p1.y() < p2.x() * FLOAT_MAX_VALUE + p2.y();
}

float distanceBetweenQPoints(QPointF first, QPointF second);

float vectorLength(QPointF vector);

float vectorAngle(QPointF vector);

bool isEqual(float first, float second, float eps = EPS);

bool isEqual(QPointF first, QPointF second, float eps = EPS);

float angleBetweenEdges(Edge first, Edge second);

QPointF rotateVector(QPointF vector, float angle);

#endif // MYMATH_H
