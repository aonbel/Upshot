#include "car.h"

Car::Car() :
    pos(QPointF()),
    angle(0),
    velocity(0),
    timer(new QTimer)
{
    timer->setInterval(TICK_TIME);
    connect(timer, &QTimer::timeout, this, &Car::Update);

    timer->start();
}

Car::Car(QPointF pos, float angle) :
    pos(pos),
    angle(angle),
    velocity(0),
    timer(new QTimer)
{
    timer->setInterval(TICK_TIME);
    connect(timer, &QTimer::timeout, this, &Car::Update);

    timer->start();
}

void Car::Rotate(float delta)
{
    angle += delta;
}

void Car::Accelerate(float delta)
{
    velocity = delta;
}

void Car::Update()
{
    if (velocity < 0)
    {
        velocity = 0;
    }

    if (velocity > MAX_SPEED)
    {
        velocity = MAX_SPEED;
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

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto vectorToPoint1 = rotateVector(QPointF(CAR_LENGTH / 2, CAR_WIDTH / 2), angle);
    auto vectorToPoint2 = rotateVector(QPointF(CAR_LENGTH / 2, -CAR_WIDTH / 2), angle);
    auto vectorToPoint3 = rotateVector(QPointF(-CAR_LENGTH / 2, -CAR_WIDTH / 2), angle);
    auto vectorToPoint4 = rotateVector(QPointF(-CAR_LENGTH / 2, CAR_WIDTH / 2), angle);

    auto point1 = pos + vectorToPoint1;
    auto point2 = pos + vectorToPoint2;
    auto point3 = pos + vectorToPoint3;
    auto point4 = pos + vectorToPoint4;

    QPolygonF poly;
    poly << point1 << point2 << point3 << point4;

    painter->save();
    painter->setPen(QPen(Qt::red));
    painter->setBrush(QBrush(Qt::red));
    painter->drawPolygon(poly);
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
