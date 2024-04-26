#include "pathservice.h"

PathService::PathService() = default;

std::map<QPointF, QVector<QPointF>* >* PathService::FromEdgesToAdjMatrix(QVector<Edge> *edges)
{
    std::map<QPointF, QVector<QPointF>*>* adjMatrix = new std::map<QPointF, QVector<QPointF>* >;
    std::map<QPointF, bool> been;

    for (auto edge : *edges)
    {
        if (!been[edge.startPos])
        {
            (*adjMatrix)[edge.startPos] = new QVector<QPointF>;
            been[edge.startPos] = 1;
        }

        if (!been[edge.endPos])
        {
            (*adjMatrix)[edge.endPos] = new QVector<QPointF>;
            been[edge.endPos] = 1;
        }

        (*adjMatrix)[edge.startPos]->push_back(edge.endPos);
    }

    return adjMatrix;
}

QVector<QPointF> *PathService::FindPath(std::map<QPointF, QVector<QPointF> *> *adjMatrix, QPointF start, QPointF end)
{
    std::map<QPointF, float> dist;
    std::map<QPointF, QPointF> prev;
    std::map<QPointF, bool> been;

    for (auto vertex : *adjMatrix)
    {
        dist[vertex.first] = FLOAT_MAX_VALUE;
        prev[vertex.first] = DEF_QPOINTF;
    }

    dist[start] = 0;
    std::queue<QPointF> queue;
    queue.push(start);

    while (!queue.empty())
    {
        auto vertex = queue.front();
        queue.pop();
        if (been[vertex])
        {
            continue;
        }
        been[vertex] = true;

        for (auto to : *(*adjMatrix)[vertex])
        {
            queue.push(to);
            if (dist[to] > dist[vertex] + 1)
            {
                dist[to] = dist[vertex] + 1;
                prev[to] = vertex;
            }
        }
    }

    if (dist[end] == FLOAT_MAX_VALUE)
    {
        return nullptr;
    }

    QVector<QPointF>* path = new QVector<QPointF>;

    QPointF curr = end;

    while (curr != DEF_QPOINTF)
    {
        path->push_back(curr);
        curr = prev[curr];
    }

    std::reverse(path->begin(), path->end());

    return path;
}
