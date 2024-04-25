#include "roadcontainer.h"

RoadContainer::RoadContainer() :
    allRoads(new QVector<Road*>)
{

}

void RoadContainer::AddRoad(const QPointF &start, const QPointF &end)
{
    QVector<Road*> prev;
    QVector<Road*> next;

    prev.push_back(nullptr);
    next.push_back(nullptr);

    for (auto road : *allRoads)
    {
        if (isEqual(road->GetEnd(), start))
        {
            prev.push_back(road);

            if (prev.size() >= 4)
            {
                break;
            }
        }
    }

    for (auto road : *allRoads)
    {
        if (isEqual(road->GetStart(), end))
        {
            next.push_back(road);

            if (next.size() >= 4)
            {
                break;
            }
        }
    }

    for (auto prevRoad : prev)
    {
        for (auto nextRoad : next)
        {
            if (prevRoad != nullptr && nextRoad != nullptr)
            {
                auto angle = angleBetweenEdges(Edge(start, end), Edge(prevRoad->GetEnd(), nextRoad->GetStart()));
                if (prevRoad == nextRoad || angle >= PI / 8)
                {
                    continue;
                }
            }

            Road* newRoad = new Road(start, end, prevRoad, nextRoad, TypeOfRoadDirection::one_way, NumberOfRoadLines::one_lane);

            allRoads->push_back(newRoad);

            emit NewRoad(newRoad);
        }
    }
}

QVector<Edge> *RoadContainer::GetGraph() const
{
    QVector<Edge>* answer = new QVector<Edge>;

    for (size_t partIter = 0;partIter<allRoads->count();++partIter)
    {
        QVector<Edge>* edges = allRoads->at(partIter)->GetEdgesForGraph();

        for (size_t edgeIter = 0;edgeIter<edges->count();++edgeIter)
        {
            answer->push_back(edges->at(edgeIter));
        }

        delete edges;
    }

    return answer;
}


