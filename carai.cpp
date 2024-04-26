#include "carai.h"

CarAI::CarAI() = default;

CarAI::CarAI(QVector<QPointF> *path, QVector<CarAI*>* carAIs) :
    car(new Car((*path)[0], 0)),
    path(path),
    timer(new QTimer),
    currPoint(1),
    carAIs(carAIs),
    processDone(false)
{
    timer->setInterval(TICK_TIME);

    timer->start();

    connect(timer, &QTimer::timeout, this, &CarAI::Update);
}

void CarAI::Update()
{
    while (isEqual(car->GetPosition(), (*path)[currPoint], SUCCESS_EPS))
    {
        currPoint++;

        if (currPoint == path->size())
        {
            delete car;
            processDone = true;
            disconnect(timer, &QTimer::timeout, this, &CarAI::Update);
            return;
        }
    }

    auto angleDelta = vectorAngle((*path)[currPoint] - car->GetPosition()) - car->GetAngle();

    if (qAbs(angleDelta + 2 * PI) < qAbs(angleDelta))
    {
        angleDelta = angleDelta + 2 * PI;
    }

    if (qAbs(angleDelta - 2 * PI) < qAbs(angleDelta))
    {
        angleDelta = angleDelta - 2 * PI;
    }

    car->Rotate(angleDelta * REACTION_COEFFICIENT);

    QPointF position = car->GetPosition();
    float angle = car->GetAngle();
    angleDelta = qAbs(angleDelta);

    QPointF rotatedVector = rotateVector(QPointF(1, 0), angle);

    float angleCoef = rotatedVector.y() / rotatedVector.x();
    float offset = position.y() - angleCoef * position.x();
    float distanceToNearestCar = MAX_VISIBILITY_LENGTH;

    for (auto carAI : *carAIs)
    {
        if (carAI->isDone() || carAI == this)
        {
            continue;
        }

        auto currPos = carAI->GetCarPosition();

        if (scalarMultiplicationVectors(rotatedVector, currPos - position) <= 0)
        {
            continue;
        }

        float currOffset = currPos.y() - angleCoef * currPos.x();
        float dist = currOffset - offset;

        if (qAbs(dist) < MAX_VISIBILITY_LENGTH)
        {
            float projectionLength = qSqrt(qPow(distanceBetweenQPoints(position, currPos), 2) - qPow(dist, 2));

            distanceToNearestCar = std::min(distanceToNearestCar, projectionLength);
        }
    }


    if (distanceToNearestCar == MAX_VISIBILITY_LENGTH)
    {
        car->Accelerate(MAX_SPEED * PI / angleDelta);
    }
    else
    {
        car->Accelerate(STOP_POINT - MAX_SPEED * MAX_VISIBILITY_LENGTH / distanceToNearestCar);
    }
}

bool CarAI::isDone()
{
    return processDone;
}

QPointF CarAI::GetCarPosition()
{
    return car->GetPosition();
}

Car* CarAI::GetCar()
{
    return car;
}
