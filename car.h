#ifndef CAR_H
#define CAR_H

#include <QtCore>
#include <QGraphicsItem>
#include <QPainter>

#include "edge.h"
#include "mymath.h"

const float CAR_LENGTH = 10;
const float CAR_WIDTH = 5;

const int UPDATES_PER_SECOND = 60;
const float TICK_TIME = 1000.0 / UPDATES_PER_SECOND;
const float MAX_ACCELERATION_DELTA = .4;
const float MAX_SPEED = 3;

class Car : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    QPointF pos;
    float angle;
    float velocity;
    QTimer* timer;
public:
    Car();
    Car(QPointF pos, float angle);
    void Rotate(float delta);
    void Accelerate(float delta);
    void Update();
    QPointF GetPosition();
    float GetAngle();
    float GetVelocity();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // CAR_H
