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
    auto dist = distanceBetweenQPoints(first, second);
    return (dist < EPS);
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
    return qAtan2(vector.y(), vector.x());
}

QPointF rotateVector(QPointF vector, float angle)
{
    return QPointF(vector.x() * qCos(angle) - vector.y() * qSin(angle),
                   vector.x() * qSin(angle) + vector.y() * qCos(angle));
}
