#ifndef EDGE_H
#define EDGE_H

#include <QtCore>

struct Edge
{
    QPointF startPos;
    QPointF endPos;

    Edge() = default;

    Edge(const QPointF& startPos, const QPointF& endPos) : startPos(startPos), endPos(endPos)
    {

    }

    void Reverse()
    {
        std::swap(startPos, endPos);
    }
};

#endif // EDGE_H
