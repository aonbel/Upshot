#ifndef ROAD_H
#define ROAD_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtMath>

#include "edge.h"
#include "roadpart.h"
#include "mymath.h"

enum TypeOfRoadDirection
{
    one_way,
    two_way
};

enum NumberOfRoadLines
{
    one_lane = 1,
    two_lanes = 2,
    four_lanes = 4
};

class Road : public RoadPart
{
private:
    int level;

    QPointF start;
    QPointF end;

    Road* prev;
    Road* next;

    TypeOfRoadDirection typeOfDir;
    NumberOfRoadLines numberOfLines;

    QVector<QPointF>* endsOfLines;
    QVector<QPointF>* startsOfLines;
public:
    Road(const QPointF& start, const QPointF& end, Road* _prev, Road* _next, TypeOfRoadDirection typeOfDir, NumberOfRoadLines numberOfLines, int level);
    Road(Road& obj);
    Road(Road&& obj) noexcept;

    void addNextRoad(Road *_next);
    void addPrevRoad(Road *_prev);

    float GetAngleOfTheRoad() const;
    QVector<Edge>* GetEdgesForGraph() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    QVector<QPointF> getEndsOfLines();
    QVector<QPointF> getStartsOfLines();

    QPointF GetStart() const;
    QPointF GetEnd() const;
};

#endif // ROAD_H
