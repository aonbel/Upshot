#ifndef CARSSPAWNER_H
#define CARSSPAWNER_H

#include "graphicscene.h"
#include "carai.h"
#include "mymath.h"
#include "pathservice.h"

const int CHANCE_OF_SPAWNING_CAR = 7;
const int MAX_CAR_COUNT = 100;

class CarsSpawner : public QObject
{
    Q_OBJECT
    GraphicScene* graphicsScene;
    QVector<CarAI*>* cars;
    QVector<QVector<RoadPoint>*>* paths;
    QTimer* timer;
    std::mt19937* rng;
public:
    CarsSpawner();
    ~CarsSpawner() override;
    CarsSpawner(QVector<RoadEdge>* edges, GraphicScene* graphicsScene);
    void Update();
};

#endif // CARSSPAWNER_H
