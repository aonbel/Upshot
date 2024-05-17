#include "car.h"

Car::Car(const Car &other)
    : pos(other.pos)
    , angle(other.angle)
    , velocity(other.velocity)
    , timer(new QTimer)
    , color(other.color)
{
    ConnectTimer();
}

Car::Car(Car &&other) noexcept
    : pos(other.pos)
    , angle(other.angle)
    , velocity(other.velocity)
    , timer(other.timer)
    , color(other.color)
{
    ConnectTimer();
    other.timer = nullptr;
}

Car::Car(RoadPoint pos, float angle)
    : pos(pos)
    , angle(angle)
    , velocity(0)
    , timer(new QTimer) 
{
    QRandomGenerator rng(std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::system_clock::now().time_since_epoch())
                             .count());

    color = colors[rng() % 4];

    ConnectTimer();
}

Car::~Car()
{
    if (timer != nullptr)
    {
        delete timer;
        timer = nullptr;
    }
}

void Car::Rotate(float delta)
{
    angle += delta;
}

void Car::setVelocity(float newVelocity)
{
    if (newVelocity < 0) {
        velocity = 0;
    } else if (newVelocity > MAX_SPEED) {
        velocity = MAX_SPEED;
    } else {
        velocity = newVelocity;
    }
}

void Car::setLevel(int newLevel)
{
    if (newLevel != pos.level)
    {
        pos.level = newLevel;
        emit needToUpdateLevelOfCar();
    }
}

void Car::Update()
{
    pos.pos.setX(pos.pos.x() + velocity * qCos(angle));
    pos.pos.setY(pos.pos.y() + velocity * qSin(angle));
}

void Car::ConnectTimer()
{
    connect(timer, &QTimer::timeout, this, &Car::Update);
    if (!timer->isActive())
    {
        timer->setInterval(TICK_TIME);
        timer->start();
    }
}

RoadPoint Car::GetPosition() const
{
    return pos;
}

RoadPoint Car::PredictPosition() const
{
    RoadPoint prediction = pos;
    prediction.pos.setX(prediction.pos.x() + velocity * qCos(angle));
    prediction.pos.setY(prediction.pos.y() + velocity * qSin(angle));
    return prediction;
}

float Car::GetAngle() const
{
    return angle;
}

float Car::GetVelocity() const
{
    return velocity;
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto vectorToPoint1 = rotateVector(QPointF(CAR_LENGTH / 2, CAR_WIDTH / 2), angle);
    auto vectorToPoint2 = rotateVector(QPointF(CAR_LENGTH / 2, -CAR_WIDTH / 2), angle);
    auto vectorToPoint3 = rotateVector(QPointF(-CAR_LENGTH / 2, -CAR_WIDTH / 2), angle);
    auto vectorToPoint4 = rotateVector(QPointF(-CAR_LENGTH / 2, CAR_WIDTH / 2), angle);

    auto point1 = pos.pos + vectorToPoint1;
    auto point2 = pos.pos + vectorToPoint2;
    auto point3 = pos.pos + vectorToPoint3;
    auto point4 = pos.pos + vectorToPoint4;

    QPolygonF poly;
    poly << point1 << point2 << point3 << point4;

    painter->save();
    painter->setPen(QPen(color));
    painter->setBrush(QBrush(color));
    painter->drawPolygon(poly);
    painter->restore();
}

QRectF Car::boundingRect() const
{
    auto point1 = QPointF(pos.pos.x() + CAR_LENGTH * qCos(angle),
                          pos.pos.y() + CAR_WIDTH * qSin(angle));
    auto point2 = QPointF(pos.pos.x() + CAR_LENGTH * qCos(angle),
                          pos.pos.y() - CAR_WIDTH * qSin(angle));
    auto point3 = QPointF(pos.pos.x() - CAR_LENGTH * qCos(angle),
                          pos.pos.y() + CAR_WIDTH * qSin(angle));
    auto point4 = QPointF(pos.pos.x() - CAR_LENGTH * qCos(angle),
                          pos.pos.y() - CAR_WIDTH * qSin(angle));

    return QRectF(QPointF(std::min({point1.x(), point2.x(), point3.x(), point4.x()}),
                          std::min({point1.y(), point2.y(), point3.y(), point4.y()})),
                  QPointF(std::max({point1.x(), point2.x(), point3.x(), point4.x()}),
                          std::max({point1.y(), point2.y(), point3.y(), point4.y()})));
}
