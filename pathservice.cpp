#include "pathservice.h"

const float MAX_VALUE = 1e9;
const QPointF DEF_QPOINTF {MAX_VALUE, MAX_VALUE};

PathService::PathService()
{

}

std::map<QPointF, QVector<QPointF>* >* PathService::FromEdgesToAdjMatrix(QVector<Edge> *edges)
{
    std::map<QPointF, QVector<QPointF>* >* adjMatrix = new std::map<QPointF, QVector<QPointF>* >;

    for (auto edge : *edges)
    {
        if ((*adjMatrix)[edge.startPos] == 0)
        {
            (*adjMatrix)[edge.startPos] = new QVector<QPointF>;
        }

        (*adjMatrix)[edge.startPos]->push_back(edge.endPos);
    }

    return adjMatrix;
}

QVector<QPointF> *PathService::FindPath(std::map<QPointF, QVector<QPointF> *> *adjMatrix, QPointF start, QPointF end)
{
    std::map<QPointF, float> dist;
    std::map<QPointF, QPointF> prev;

    for (auto vertex : *adjMatrix)
    {
        dist[vertex.first] = MAX_VALUE;
        prev[start] = DEF_QPOINTF;
    }

    dist[start] = 0;
    std::queue<QPointF> queue;
    queue.push(start);

    while (!queue.empty())
    {
        auto vertex = queue.back();
        queue.pop();
        if (dist[vertex] != MAX_VALUE)
        {
            continue;
        }

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

    if (dist[end] == MAX_VALUE)
    {
        return nullptr;
    }

    QVector<QPointF>* path;

    QPointF curr = end;

    while (curr != DEF_QPOINTF)
    {
        path->push_back(curr);
        curr = prev[curr];
    }

    return path;
}
