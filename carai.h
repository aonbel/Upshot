#ifndef CARAI_H
#define CARAI_H

#include "car.h"
#include "mymath.h"

#include <QTimer>
#include <QtCore>

const float MAX_VISIBILITY_LENGTH = 4 * CAR_LENGTH;
const float MAX_VISIBILITY_WIDTH = 1.5 * CAR_WIDTH;
const float REACTION_COEFFICIENT = 0.025 * MAX_SPEED;
const float SUCCESS_EPS = 20;
const float STOP_POINT = 2 * CAR_LENGTH;

class CarAI : public QObject
{
    Q_OBJECT
private:
    Car* car;
    QVector<RoadPoint>* path;
    int currPoint;
    QTimer* timer;
    QVector<CarAI*>* carAIs;
    bool processDone;
public:
    CarAI();
    CarAI(QVector<RoadPoint>* path, QVector<CarAI*>* carAIs);
    void Update();
    bool isDone();
    RoadPoint GetCarPosition();
    Car* GetCar();
};

#endif // CARAI_H
