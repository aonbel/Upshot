#ifndef ROADCONTAINER_H
#define ROADCONTAINER_H

#include "road.h"
#include "roadbrush.h"
#include "roadedge.h"
#include "inputprocesser.h"

const float SENSITIVITY = 0.5 * DEFAULT_SEGMENT_LENGTH;

class RoadContainer : public QObject
{
    Q_OBJECT
private:
    QVector<Road*>* allRoads;
public:
    RoadContainer();
    void Clear();
    void AddRoad(const QPointF &start, const QPointF &end, RoadBrush brushOnStart = RoadBrush(), RoadBrush brushOnEnd = RoadBrush());
    QVector<RoadEdge>* GetGraph() const;
signals:
    void NewRoad(Road* road);
    void RemoveRoad(Road* road);
};

#endif // ROADCONTAINER_H
