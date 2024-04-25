#ifndef ROADCONTAINER_H
#define ROADCONTAINER_H

#include "road.h"

class RoadContainer : public QObject
{
    Q_OBJECT
private:
    QVector<Road*>* allRoads;
public:
    RoadContainer();
    void AddRoad(const QPointF& start, const QPointF& end);
    QVector<Edge>* GetGraph() const;
signals:
    void NewRoad(Road* road);
};

#endif // ROADCONTAINER_H
