#include "carai.h"

CarAI::CarAI(const CarAI &other) :
    car(nullptr),
    path(other.path),
    timer(nullptr),
    currPoint(other.currPoint),
    carAIs(other.carAIs),
    processDone(other.processDone),
    graphicsScene(other.graphicsScene)
{
    if (other.car != nullptr)
    {
        car = new Car(*other.car);

        connect(car, &Car::needToUpdateLevelOfCar, this, [&] () {
            graphicsScene->setItemLayer(car, car->GetPosition().level);
        });

        emit car->needToUpdateLevelOfCar();
    }

    if (other.timer != nullptr)
    {
        timer = new QTimer;

        timer->setInterval(TICK_TIME);
        connect(timer, &QTimer::timeout, this, &CarAI::Update);

        timer->start();
    }
}

CarAI::CarAI(CarAI &&other) noexcept :
    car(other.car),
    path(other.path),
    timer(other.timer),
    currPoint(other.currPoint),
    carAIs(other.carAIs),
    processDone(other.processDone),
    graphicsScene(other.graphicsScene)
{
    if (timer != nullptr)
    {
        connect(timer, &QTimer::timeout, this, &CarAI::Update);
    }

    if (car != nullptr)
    {
        connect(car, &Car::needToUpdateLevelOfCar, this, [&] () {
            graphicsScene->setItemLayer(car, car->GetPosition().level);
        });
    }

    other.car = nullptr;
    other.timer = nullptr;
    other.path = nullptr;
    other.carAIs = nullptr;
    other.graphicsScene = nullptr;
}

CarAI::CarAI(const QVector<RoadPoint> *path, const QVector<CarAI>* carAIs, GraphicScene* graphicsScene) :
    car(new Car((*path)[0], vectorAngle((*path)[1].pos - (*path)[0].pos))),
    path(path),
    timer(new QTimer),
    currPoint(1),
    carAIs(carAIs),
    processDone(false),
    graphicsScene(graphicsScene)
{
    timer->setInterval(TICK_TIME);
    connect(timer, &QTimer::timeout, this, &CarAI::Update);

    connect(car, &Car::needToUpdateLevelOfCar, this, [&] () {
        graphicsScene->setItemLayer(car, car->GetPosition().level);
    });

    timer->start();
    emit car->needToUpdateLevelOfCar();
}

CarAI::~CarAI()
{
    ForceStop();
}

void CarAI::Update()
{
    while (isEqual(car->GetPosition().pos, (*path)[currPoint].pos, SUCCESS_EPS))
    {
        car->setLevel((*path)[currPoint++].level);

        if (currPoint == path->size())
        {
            ForceStop();
            return;
        }
    }

    QPointF position = car->GetPosition().pos;
    int level = car->GetPosition().level;
    float angle = car->GetAngle();
    QPointF rotatedVector = rotateVector(QPointF(1, 0), angle);

    auto angleDelta = angleBetweenVectors((*path)[currPoint].pos - position, rotatedVector);

    car->Rotate(angleDelta * REACTION_COEFFICIENT);
    angleDelta = qAbs(angleDelta);

    float angleCoef = rotatedVector.y() / rotatedVector.x();
    float offset = position.y() - angleCoef * position.x();
    float distanceToNearestCar = MAX_VISIBILITY_LENGTH;

    for (int iter = 0;iter < carAIs->size(); ++iter)
    {
        if ((*carAIs)[iter].isDone() || (*carAIs)[iter].GetCar() == car)
        {
            continue;
        }

        QPointF currPos = (*carAIs)[iter].GetCar()->PredictPosition().pos;
        int currLevel = (*carAIs)[iter].GetCar()->PredictPosition().level;

        if (currLevel != level || scalarMultiplicationVectors(currPos - position, rotatedVector) < 0)
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

void CarAI::ForceStop()
{
    if (car != nullptr)
    {
        delete car;
        car = nullptr;
    }

    if (timer != nullptr)
    {
        delete timer;
        timer = nullptr;
    }

    processDone = true;
}

bool CarAI::isDone() const
{
    return processDone;
}

Car* CarAI::GetCar() const
{
    return car;
}
