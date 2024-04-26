#include "carsspawner.h"

CarsSpawner::CarsSpawner() :
    graphicsScene(nullptr),
    paths(new QVector<QVector<QPointF>*>),
    cars(new QVector<CarAI*>),
    timer(new QTimer),
    rng(new std::mt19937(time(0)))
{
    timer->setInterval(TICK_TIME);
    connect(timer, &QTimer::timeout, this, &CarsSpawner::Update);
    timer->start();
}

CarsSpawner::CarsSpawner(QVector<Edge> *edges, GraphicScene *graphicsScene) :
    graphicsScene(graphicsScene),
    paths(new QVector<QVector<QPointF>*>),
    cars(new QVector<CarAI*>),
    timer(new QTimer),
    rng(new std::mt19937(time(nullptr)))
{
    QVector<QPointF> starts;
    QVector<QPointF> ends;

    {
        std::map<QPointF, int> incomingCount;
        std::map<QPointF, int> outcomingCount;

        for (auto edge : *edges)
        {
            incomingCount[edge.endPos]++;
            incomingCount[edge.startPos];
            outcomingCount[edge.startPos]++;
            outcomingCount[edge.endPos];
        }

        for (auto point : outcomingCount)
        {
            if (point.second == 0)
            {
                ends.push_back(point.first);
            }
        }

        for (auto point : incomingCount)
        {
            if (point.second == 0)
            {
                starts.push_back(point.first);
            }
        }
    }

    auto adj = PathService::FromEdgesToAdjMatrix(edges);

    for (auto start : starts)
    {
        for (auto end : ends)
        {
            auto path = PathService::FindPath(adj, start, end);

            if (path != nullptr)
            {
                paths->push_back(path);
            }
        }
    }

    timer->setInterval(TICK_TIME);
    connect(timer, &QTimer::timeout, this, &CarsSpawner::Update);
    timer->start();
}

void CarsSpawner::Update()
{
    if ((*rng)() % 10 == 0)
    {
        auto pos = (*rng)() % paths->size();

        bool isCarNear = false;

        for (auto carAI : *cars)
        {
            if (isEqual(carAI->GetCarPosition(), paths->at(pos)->at(0), CAR_LENGTH))
            {
                isCarNear = true;
            }
        }

        if (!isCarNear)
        {
            cars->push_back(new CarAI(paths->at(pos), cars));

            graphicsScene->addItem(cars->back()->GetCar());
        }
    }

    for (size_t iter = 0;iter < cars->size();++iter)
    {
        if (cars->at(iter)->isDone())
        {
            delete cars->at(iter);
            cars->erase(std::next(cars->begin(), iter));
            iter = 0;
        }
    }
}

