#include "roadcontainer.h"

RoadContainer::RoadContainer() :
    allRoads(new QVector<Road*>)
{

}

void RoadContainer::AddRoad(const QPointF &start, const QPointF &end, RoadBrush brushOnStart, RoadBrush brushOnEnd)
{
    Road* newRoad = new Road(RoadPoint(start, brushOnStart.GetLevel()), RoadPoint(end, brushOnEnd.GetLevel()), brushOnStart.GetType(), brushOnStart.GetNumberOfLines(), brushOnStart.GetLevel());

    for (auto road : *allRoads)
    {
        if (isEqual(road->GetStart().pos, start, SENSITIVITY))
        {
            newRoad->connectStartToStartOf(road);
        }

        if (isEqual(road->GetStart().pos, end, SENSITIVITY))
        {
            newRoad->connectEndToStartOf(road);
        }

        if (isEqual(road->GetEnd().pos, start, SENSITIVITY))
        {
            newRoad->connectStartToEndOf(road);
        }

        if (isEqual(road->GetEnd().pos, end, SENSITIVITY))
        {
            newRoad->connectEndToEndOf(road);
        }
    }

    allRoads->push_back(newRoad);

    emit NewRoad(newRoad);
}

QVector<RoadEdge> *RoadContainer::GetGraph() const
{
    QVector<RoadEdge>* answer = new QVector<RoadEdge>;

    for (size_t partIter = 0;partIter<allRoads->count();++partIter)
    {
        QVector<RoadEdge>* edges = allRoads->at(partIter)->GetEdgesForGraph();

        for (size_t edgeIter = 0;edgeIter<edges->count();++edgeIter)
        {
            answer->push_back(edges->at(edgeIter));
        }

        delete edges;
    }

    return answer;
}


