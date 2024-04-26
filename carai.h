#ifndef CARAI_H
#define CARAI_H

#include "car.h"
#include "mymath.h"

#include <QTimer>
#include <QtCore>

const float MAX_VISIBILITY_LENGTH = CAR_LENGTH;
const float MAX_VISIBILITY_WIDTH = 3 * CAR_LENGTH;
const float REACTION_COEFFICIENT = 0.3;
const float SUCCESS_EPS = 10;
const float STOP_POINT = 0.05 * CAR_LENGTH;

class CarAI : public QObject
{
    Q_OBJECT
private:
    Car* car;
    QVector<QPointF>* path;
    int currPoint;
    QTimer* timer;
    QVector<CarAI*>* carAIs;
    bool processDone;
public:
    CarAI();
    CarAI(QVector<QPointF>* path, QVector<CarAI*>* carAIs);
    void Update();
    bool isDone();
    QPointF GetCarPosition();
    Car* GetCar();
};

#endif // CARAI_H
