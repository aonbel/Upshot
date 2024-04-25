#ifndef CAR_H
#define CAR_H

#include <QtCore>
#include <QGraphicsItem>
#include <QPainter>

#include "edge.h"
#include "mymath.h"

const float CAR_LENGTH = 10;
const float CAR_WIDTH = 5;

class Car : public QGraphicsItem
{
private:
    QPointF pos;
    float angle;
    float velocity;
    float acceleration;
public:
    Car();
    Car(QPointF pos, float angle);
    void Rotate(float delta);
    void Accelerate(float delta);
    void Update();
    QPointF GetPosition();
    float GetAngle();
    float GetVelocity();
    float GetAcceleration();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // CAR_H
