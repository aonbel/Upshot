#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "roadpart.h"
#include "road.h"

class Intersection : RoadPart
{
private:
    QVector<QPointF>* in;
    QVector<QPointF>* out;

    QPointF minPos;
    QPointF maxPos;

public:
    Intersection();

    void AddRoadAll(Road* road);
    void AddRoadStarts(Road* road);
    void AddRoadEnds(Road* road);

    bool Empty() const;

    QVector<Edge>* GetEdgesForGraph() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // INTERSECTION_H
