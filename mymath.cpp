#include "mymath.h"

bool isEqual(float first, float second, float eps)
{
    return qAbs(first - second) <= eps;
}

bool isEqual(QPointF first, QPointF second, float eps)
{
    auto dist = vectorLength(first - second);
    return (dist < eps);
}

float angleBetweenVectors(QPointF first, QPointF second)
{
    auto angleDelta = vectorAngle(first) - vectorAngle(second);

    if (angleDelta >= PI) {
        angleDelta -= 2 * PI;
    }

    if (angleDelta <= -PI) {
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
    return {vector.x() * qCos(angle) - vector.y() * qSin(angle),
            vector.x() * qSin(angle) + vector.y() * qCos(angle)};
}

float scalarMultiplicationVectors(QPointF first, QPointF second)
{
    return first.x() * second.x() + first.y() * second.y();
}
