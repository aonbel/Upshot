#ifndef CARAI_H
#define CARAI_H

#include "car.h"
#include "mymath.h"

#include <QTimer>
#include <QtCore>

const float RATIO_OF_STOPING_FREE = 0.8;
const float RATIO_OF_STOPING_IN_FRONT = 0.3;
const float MAX_VISIBILITY_LENGTH = 25.0;
const float MAX_VISIBILITY_WIDTH = 2 * CAR_LENGTH;
const float REACTION_COEFFICIENT = 0.3;
const float SUCCESS_EPS = 20;

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
