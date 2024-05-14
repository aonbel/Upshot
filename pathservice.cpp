#include "pathservice.h"

PathService::PathService() = default;

std::map<RoadPoint, QVector<RoadPoint> *> *PathService::FromEdgesToAdjMatrix(QVector<RoadEdge> *edges)
{
    std::map<RoadPoint, QVector<RoadPoint> *> *adjMatrix
        = new std::map<RoadPoint, QVector<RoadPoint> *>;
    std::map<RoadPoint, bool> been;

    for (auto edge : *edges) {
        if (!been[edge.startPos]) {
            (*adjMatrix)[edge.startPos] = new QVector<RoadPoint>;
            been[edge.startPos] = true;
        }

        if (!been[edge.endPos]) {
            (*adjMatrix)[edge.endPos] = new QVector<RoadPoint>;
            been[edge.endPos] = true;
        }

        (*adjMatrix)[edge.startPos]->push_back(edge.endPos);
    }

    return adjMatrix;
}

QVector<RoadPoint> *PathService::FindPath(std::map<RoadPoint, QVector<RoadPoint> *> *adjMatrix,
                                          RoadPoint start,
                                          RoadPoint end)
{
    std::map<RoadPoint, float> dist;
    std::map<RoadPoint, RoadPoint> prev;
    std::map<RoadPoint, bool> been;

    for (auto vertex : *adjMatrix) {
        dist[vertex.first] = FLOAT_MAX_VALUE;
        prev[vertex.first] = RoadPoint();
    }

    dist[start] = 0;
    std::queue<RoadPoint> queue;
    queue.push(start);

    while (!queue.empty()) {
        auto vertex = queue.front();
        queue.pop();
        if (been[vertex]) {
            continue;
        }
        been[vertex] = true;

        for (auto to : *(*adjMatrix)[vertex]) {
            if (dist[to] > dist[vertex] + 1) {
                queue.push(to);
                dist[to] = dist[vertex] + 1;
                prev[to] = vertex;
            }
        }
    }

    if (dist[end] == FLOAT_MAX_VALUE) {
        return nullptr;
    }

    QVector<RoadPoint> *path = new QVector<RoadPoint>;

    RoadPoint curr = end;

    while (curr != RoadPoint()) {
        path->push_back(curr);
        curr = prev[curr];
    }

    std::reverse(path->begin(), path->end());

    return path;
}
