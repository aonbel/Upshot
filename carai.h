#ifndef CARAI_H
#define CARAI_H

#include "car.h"
#include "mymath.h"

#include <QTimer>
#include <QtCore>
#include "graphicscene.h"

const float MAX_VISIBILITY_LENGTH = 6 * CAR_LENGTH;
const float MAX_VISIBILITY_WIDTH = 1.2 * CAR_WIDTH;
const float REACTION_COEFFICIENT = 0.025 * MAX_SPEED;
const float SUCCESS_EPS = 20;
const float STOP_POINT = 2 * CAR_LENGTH;

class CarAI : public QObject
{
    Q_OBJECT
private:
    GraphicScene* graphicsScene;
    Car* car;
    const QVector<RoadPoint>* path;
    int currPoint;
    QTimer* timer;
    const QVector<CarAI>* carAIs;
    bool processDone;
public:
    CarAI(const CarAI& other);
    CarAI(CarAI&& other) noexcept;
    CarAI(const QVector<RoadPoint>* path, const QVector<CarAI>* carAIs, GraphicScene* graphicsScene);
    ~CarAI() override;
    void Update();
    void ForceStop();
    bool isDone() const;
    Car* GetCar() const;
};

#endif // CARAI_H
