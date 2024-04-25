#ifndef ROADPART_H
#define ROADPART_H

#include <QGraphicsItem>
#include <QPainter>

#include "edge.h"

const float WIDTH_OF_LINE = 20;

class RoadPart : public QGraphicsItem
{
public:
    RoadPart();
    virtual QVector<Edge>* GetEdgesForGraph() const;
};

#endif // ROADPART_H
