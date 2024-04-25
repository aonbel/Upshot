#ifndef CARAI_H
#define CARAI_H

#include "car.h"
#include "mymath.h"

#include <QTimer>
#include <QtCore>

const float RATIO_OF_STOPING_TO_INCREASING_SPEED = 0.75;
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
    void Update();
    QPointF GetCarPosition();
    Car* GetCar();
};

#endif // CARAI_H
