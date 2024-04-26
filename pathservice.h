#ifndef PATHSERVICE_H
#define PATHSERVICE_H

#include "mymath.h"

class PathService
{
public:
    PathService();
    static std::map<QPointF, QVector<QPointF>* >* FromEdgesToAdjMatrix(QVector<Edge>* edges);
    static QVector<QPointF>* FindPath(std::map<QPointF, QVector<QPointF>* >* adjMatrix, QPointF start, QPointF end);
};

#endif // PATHSERVICE_H
