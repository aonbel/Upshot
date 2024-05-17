#include "carsspawner.h"

CarsSpawner::CarsSpawner(QVector<RoadEdge> *edges, GraphicScene *graphicsScene)
    : graphicsScene(graphicsScene)
    , paths(new QVector<QVector<RoadPoint> *>)
    , carAIs(new QVector<CarAI>)
    , timer(new QTimer)
    , rng(new std::mt19937(time(nullptr)))
{
    QVector<RoadPoint> starts;
    QVector<RoadPoint> ends;

    {
        std::map<RoadPoint, int> incomingCount;
        std::map<RoadPoint, int> outcomingCount;

        for (auto edge : *edges) {
            incomingCount[edge.endPos]++;
            incomingCount[edge.startPos];
            outcomingCount[edge.startPos]++;
            outcomingCount[edge.endPos];
        }

        for (auto point : outcomingCount) {
            if (point.second == 0) {
                ends.push_back(point.first);
            }
        }

        for (auto point : incomingCount) {
            if (point.second == 0) {
                starts.push_back(point.first);
            }
        }
    }

    auto adj = PathService::FromEdgesToAdjMatrix(edges);

    for (auto start : starts) {
        for (auto end : ends) {
            auto path = PathService::FindPath(adj, start, end);

            if (path != nullptr) {
                paths->push_back(path);
            }
        }
    }

    timer->setInterval(TICK_TIME);
    connect(timer, &QTimer::timeout, this, &CarsSpawner::Update);
    timer->start();
}

CarsSpawner::~CarsSpawner()
{
    delete carAIs;
    delete paths;
    delete timer;
    delete rng;
}

void CarsSpawner::Update()
{
    if (paths->empty()) {
        return;
    }

    if ((*rng)() % CHANCE_OF_SPAWNING_CAR == 0 && carAIs->size() < MAX_CAR_COUNT) {
        auto pos = (*rng)() % paths->size();

        bool isCarNear = false;

        for (int iter = 0;iter<carAIs->size();++iter)
        {
            if (!(*carAIs)[iter].isDone() && isEqual((*carAIs)[iter].GetCar()->GetPosition().pos, paths->at(pos)->at(0).pos, CAR_LENGTH)) {
                isCarNear = true;
            }
        }

        if (!isCarNear) {
            carAIs->push_back(CarAI(paths->at(pos), carAIs, graphicsScene));
        }
    }

    for (size_t iter = 0; iter < carAIs->size(); ++iter) {
        if ((*carAIs)[iter].isDone()) {
            carAIs->erase(carAIs->begin() + iter);
            --iter;
        }
    }
}
