#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QPainter>
#include <chrono>

#include "mymath.h"
#include "roadpoint.h"

const float CAR_LENGTH = 10;
const float CAR_WIDTH = 5;

const int UPDATES_PER_SECOND = 60;
const float TICK_TIME = 1000.0 / UPDATES_PER_SECOND;
const float MAX_SPEED = 6;

const QColor colors[4] = {QColor(255,0,0), QColor(0,255,0), QColor(0,0,255), QColor(255,20,147)};

class Car : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    RoadPoint pos;
    float angle;
    float velocity;
    QTimer* timer;
    QColor color;
public:
    Car(RoadPoint pos, float angle);
    void Rotate(float delta);
    void setVelocity(float newVelocity);
    void Update();
    RoadPoint GetPosition();
    RoadPoint PredictPosition();
    float GetAngle();
    float GetVelocity();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // CAR_H
