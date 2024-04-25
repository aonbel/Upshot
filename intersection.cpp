#include "intersection.h"

Intersection::Intersection() = default;

void Intersection::AddRoadAll(Road *road)
{
    AddRoadStarts(road);
    AddRoadEnds(road);
}

void Intersection::AddRoadStarts(Road *road)
{
    for (auto start : road->getStartsOfLines())
    {
        out->push_back(start);

        if (minPos.x() > start.x())
        {
            minPos.setX(start.x());
        }

        if (minPos.y() > start.y())
        {
            minPos.setY(start.y());
        }

        if (maxPos.x() < start.x())
        {
            maxPos.setX(start.x());
        }

        if (maxPos.y() < start.y())
        {
            maxPos.setY(start.y());
        }
    }
}

void Intersection::AddRoadEnds(Road *road)
{
    for (auto end : road->getEndsOfLines())
    {
        in->push_back(end);

        if (minPos.x() > end.x())
        {
            minPos.setX(end.x());
        }

        if (minPos.y() > end.y())
        {
            minPos.setY(end.y());
        }

        if (maxPos.x() < end.x())
        {
            maxPos.setX(end.x());
        }

        if (maxPos.y() < end.y())
        {
            maxPos.setY(end.y());
        }
    }
}

bool Intersection::Empty() const
{
    return in->empty() || out->empty();
}

QVector<Edge>* Intersection::GetEdgesForGraph() const
{
    QVector<Edge>* answer = new QVector<Edge>;

    for (auto start : *in)
    {
        for (auto end : *out)
        {
            answer->push_back(Edge(start, end));
        }
    }

    return answer;
}

/// REDO

void Intersection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF* points = new QPointF[4];

    points[0] = minPos;
    points[1] = QPointF(minPos.x(), maxPos.y());
    points[2] = maxPos;
    points[3] = QPointF(maxPos.x(), minPos.y());

    painter->drawPolygon(points, 4);
}

QRectF Intersection::boundingRect() const
{
    return { QRectF(minPos, maxPos) };
}
