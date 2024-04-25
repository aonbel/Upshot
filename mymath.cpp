#include "mymath.h"

float distanceBetweenQPoints(QPointF first, QPointF second)
{
    QPointF diff = first - second;
    return qSqrt(qPow(diff.x(), 2) + qPow(diff.y(), 2));
}

bool isEqual(float first, float second)
{
    return qAbs(first - second) <= EPS;
}

bool isEqual(QPointF first, QPointF second)
{
    return distanceBetweenQPoints(first, second) <= EPS;
}

float angleBetweenEdges(Edge first, Edge second)
{
    QPointF firstVector(first.endPos - first.startPos);
    QPointF secondVector(second.endPos - second.startPos);

    return vectorAngle(secondVector) - vectorAngle(firstVector);
}

float vectorLength(QPointF vector)
{
    return qSqrt(qPow(vector.x(), 2) + qPow(vector.y(), 2));
}

float vectorAngle(QPointF vector)
{
    return qAcos(vector.x() / vectorLength(vector));
}
