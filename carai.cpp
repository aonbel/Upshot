#include "carai.h"

CarAI::CarAI() = default;

CarAI::CarAI(QVector<RoadPoint> *path, QVector<CarAI*>* carAIs) :
    car(new Car((*path)[0], vectorAngle((*path)[1].pos - (*path)[0].pos))),
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
    while (isEqual(car->GetPosition().pos, (*path)[currPoint].pos, SUCCESS_EPS))
    {
        currPoint++;

        if (currPoint == path->size())
        {
            processDone = true;
            disconnect(timer, &QTimer::timeout, this, &CarAI::Update);
            return;
        }
    }

    QPointF position = car->GetPosition().pos;
    float angle = car->GetAngle();
    QPointF rotatedVector = rotateVector(QPointF(1, 0), angle);

    auto angleDelta = angleBetweenVectors((*path)[currPoint].pos - position, rotatedVector);

    car->Rotate(angleDelta * REACTION_COEFFICIENT);

    angleDelta = qAbs(angleDelta);
    float angleCoef = rotatedVector.y() / rotatedVector.x();
    float offset = position.y() - angleCoef * position.x();
    float distanceToNearestCar = MAX_VISIBILITY_LENGTH;

    for (auto carAI : *carAIs)
    {
        if (carAI->isDone() || carAI == this)
        {
            continue;
        }

        auto currPos = carAI->GetCar()->PredictPosition().pos;

        if (scalarMultiplicationVectors(currPos - position, rotatedVector) < 0)
        {
            continue;
        }

        float currOffset = currPos.y() - angleCoef * currPos.x();
        float dist = qAbs(qSin(angle - PI / 2) * (currOffset - offset));

        if (dist < MAX_VISIBILITY_WIDTH)
        {
            float projectionLength = qSqrt(qPow(vectorLength(position - currPos), 2) - qPow(dist, 2));

            if (distanceToNearestCar > projectionLength)
            {
                distanceToNearestCar = projectionLength;
            }
        }
    }

    car->setVelocity(MAX_SPEED * ((distanceToNearestCar - STOP_POINT) / MAX_VISIBILITY_LENGTH) * ((PI - angleDelta) / PI));
}

bool CarAI::isDone()
{
    return processDone;
}

RoadPoint CarAI::GetCarPosition()
{
    return car->GetPosition();
}

Car* CarAI::GetCar()
{
    return car;
}
