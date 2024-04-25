#include "car.h"

Car::Car() = default;

Car::Car(QPointF pos, float angle) :
    pos(pos),
    angle(angle),
    velocity(0),
    acceleration(0)
{

}

void Car::Rotate(float delta)
{
    angle += delta;
}

void Car::Accelerate(float delta)
{
    acceleration += delta;
}

void Car::Update()
{
    velocity += acceleration;

    if (velocity < 0)
    {
        velocity = 0;
    }

    pos.setX(pos.x() + velocity * qCos(angle));
    pos.setY(pos.y() + velocity * qSin(angle));
}

QPointF Car::GetPosition()
{
    return pos;
}

float Car::GetAngle()
{
    return angle;
}

float Car::GetVelocity()
{
    return velocity;
}

float Car::GetAcceleration()
{
    return acceleration;
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->translate(pos);
    painter->rotate(angle);
    painter->setPen(QPen(Qt::red));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-CAR_LENGTH/2, -CAR_WIDTH/2, CAR_LENGTH, CAR_WIDTH);
    painter->restore();
}

QRectF Car::boundingRect() const
{
    auto point1 = QPointF(pos.x() + CAR_LENGTH * qCos(angle), pos.y() + CAR_WIDTH * qSin(angle));
    auto point2 = QPointF(pos.x() + CAR_LENGTH * qCos(angle), pos.y() - CAR_WIDTH * qSin(angle));
    auto point3 = QPointF(pos.x() - CAR_LENGTH * qCos(angle), pos.y() + CAR_WIDTH * qSin(angle));
    auto point4 = QPointF(pos.x() - CAR_LENGTH * qCos(angle), pos.y() - CAR_WIDTH * qSin(angle));

    return QRectF(QPointF(std::min({ point1.x(), point2.x(), point3.x(), point4.x()}), std::min({ point1.y(), point2.y(), point3.y(), point4.y()})),
                  QPointF(std::max({ point1.x(), point2.x(), point3.x(), point4.x()}), std::max({ point1.y(), point2.y(), point3.y(), point4.y()})));
}
