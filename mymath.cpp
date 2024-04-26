#include "mymath.h"

float distanceBetweenQPoints(QPointF first, QPointF second)
{
    QPointF diff = first - second;
    return qSqrt(qPow(diff.x(), 2) + qPow(diff.y(), 2));
}

bool isEqual(float first, float second, float eps)
{
    return qAbs(first - second) <= eps;
}

bool isEqual(QPointF first, QPointF second, float eps)
{
    auto dist = distanceBetweenQPoints(first, second);
    return (dist < eps);
}

float angleBetweenEdges(Edge first, Edge second)
{
    QPointF firstVector(first.endPos - first.startPos);
    QPointF secondVector(second.endPos - second.startPos);

    auto angleDelta = vectorAngle(secondVector) - vectorAngle(firstVector);

    if (angleDelta > PI)
    {
        angleDelta -= 2 * PI;
    }

    if (angleDelta < -PI)
    {
        angleDelta += 2 * PI;
    }

    return angleDelta;
}

float vectorLength(QPointF vector)
{
    return qSqrt(qPow(vector.x(), 2) + qPow(vector.y(), 2));
}

float vectorAngle(QPointF vector)
{
    auto angle = qAtan2(vector.y(), vector.x());

    return angle;
}

QPointF rotateVector(QPointF vector, float angle)
{
    return {vector.x() * qCos(angle) - vector.y() * qSin(angle), vector.x() * qSin(angle) + vector.y() * qCos(angle)};
}

float scalarMultiplicationVectors(QPointF first, QPointF second)
{
    return first.x() * second.x() + first.y() * second.y();
}
