#ifndef PATHSERVICE_H
#define PATHSERVICE_H

#include "mymath.h"
#include "roadedge.h"

class PathService
{
public:
    PathService();
    static std::map<RoadPoint, QVector<RoadPoint>* >* FromEdgesToAdjMatrix(QVector<RoadEdge>* edges);
    static QVector<RoadPoint>* FindPath(std::map<RoadPoint, QVector<RoadPoint>* >* adjMatrix, RoadPoint start, RoadPoint end);
};

#endif // PATHSERVICE_H
