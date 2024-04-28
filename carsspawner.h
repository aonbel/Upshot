#ifndef CARSSPAWNER_H
#define CARSSPAWNER_H

#include "graphicscene.h"
#include "carai.h"
#include "mymath.h"
#include "pathservice.h"

class CarsSpawner : public QObject
{
    Q_OBJECT
    GraphicScene* graphicsScene;
    QVector<CarAI*>* cars;
    QVector<QVector<QPointF>*>* paths;
    QTimer* timer;
    std::mt19937* rng;
public:
    CarsSpawner();
    ~CarsSpawner() override;
    CarsSpawner(QVector<Edge>* edges, GraphicScene* graphicsScene);
    void Update();
};

#endif // CARSSPAWNER_H
