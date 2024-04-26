#include "roadcontainer.h"

RoadContainer::RoadContainer() :
    allRoads(new QVector<Road*>)
{

}

void RoadContainer::AddRoad(const QPointF &start, const QPointF &end)
{
    Road* newRoad = new Road(start, end, nullptr, nullptr, TypeOfRoadDirection::one_way, NumberOfRoadLines::one_lane);

    for (auto road : *allRoads)
    {
        if (isEqual(road->GetEnd(), start, SENSITIVITY))
        {
            newRoad->addPrevRoad(road);
        }
    }

    for (auto road : *allRoads)
    {
        if (isEqual(road->GetStart(), end, SENSITIVITY))
        {
            newRoad->addNextRoad(road);
        }
    }

    allRoads->push_back(newRoad);

    emit NewRoad(newRoad);
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


