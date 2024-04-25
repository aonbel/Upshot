#ifndef CARAI_H
#define CARAI_H

#include "car.h"
#include "mymath.h"

#include <QTimer>
#include <QtCore>

const int UPDATES_PER_SECOND = 60;
const float MAX_ACCELERATION_DELTA = 3;
const float RATIO_OF_STOPING_TO_INCREASING_SPEED = 0.75;
const float TICK_TIME = 1000.0 / UPDATES_PER_SECOND;
const float MAX_VISIBILITY_DISTANCE = 100.0;

class CarAI : public QObject
{
    Q_OBJECT
private:
    Car* car;
    QVector<QPointF>* path;
    int currPoint;
    QTimer* timer;
    QVector<CarAI*>* carAIs;
public:
    CarAI();
    CarAI(QVector<QPointF>* path, QVector<CarAI*>* carAIs);
    void UpdadeCondition();
    QPointF GetCarPosition();
    Car* GetCar();
};

#endif // CARAI_H
