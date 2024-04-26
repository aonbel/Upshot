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
    if (isEqual(car->GetPosition(), (*path)[currPoint]))
    {
        currPoint++;

        if (currPoint == path->size())
        {
            delete car;
            processDone = true;
            timer->stop();
            return;
        }
    }

    auto angleDelta = vectorAngle((*path)[currPoint] - car->GetPosition()) - car->GetAngle();

    car->Rotate(angleDelta / 2);

    QPointF position = car->GetPosition();
    float angle = car->GetAngle();
    angleDelta = qAbs(angleDelta);
    float angleCoef = qTan(car->GetAngle());
    float offset = position.x() - angleCoef * position.y();
    float distanceToNearestCar = MAX_VISIBILITY_DISTANCE;

    for (auto carAI : *carAIs)
    {
        auto currPos = carAI->GetCarPosition();

        if (qAbs(angleBetweenEdges(Edge(position, currPos), Edge(position, QPointF(position.x() + qCos(angle), position.x() + qSin(angle))))) > PI / 2)
        {
            continue;
        }

        float currOffset = currPos.x() - angleCoef * currPos.y();
        float dist = currOffset - offset;

        if (dist < CAR_LENGTH / 2)
        {
            float projectionLength = qSqrt(qPow(distanceBetweenQPoints(position, currPos), 2) - qPow(dist, 2));

            distanceToNearestCar = std::min(distanceToNearestCar, std::max(projectionLength - CAR_LENGTH, .0f));
        }
    }

    car->Accelerate(MAX_ACCELERATION_DELTA * (-angleDelta / PI + 1 - (RATIO_OF_STOPING_TO_INCREASING_SPEED + (1 - RATIO_OF_STOPING_TO_INCREASING_SPEED) * ((MAX_VISIBILITY_DISTANCE - distanceToNearestCar) / MAX_VISIBILITY_DISTANCE))));
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
