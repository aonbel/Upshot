#include "roadcontainer.h"

RoadContainer::RoadContainer() :
    allRoads(new QVector<Road*>)
{

}

void RoadContainer::Clear()
{
    for (auto road : *allRoads)
    {
        emit RemoveRoad(road);
    }
    allRoads->clear();
}

void RoadContainer::AddRoad(const QPointF &start, const QPointF &end, RoadBrush brushOnStart, RoadBrush brushOnEnd)
{
    Road* newRoad = new Road(RoadPoint(start, brushOnStart.GetLevel()), RoadPoint(end, brushOnEnd.GetLevel()), brushOnStart.GetType(), brushOnStart.GetNumberOfLines());

    for (auto road : *allRoads)
    {
        if (isEqual(road->GetStart().pos, start, SENSITIVITY) && road->GetStart().level == brushOnStart.GetLevel())
        {
            newRoad->connectStartToStartOf(road);
        }

        if (isEqual(road->GetStart().pos, end, SENSITIVITY) && road->GetStart().level == brushOnEnd.GetLevel())
        {
            newRoad->connectEndToStartOf(road);
        }

        if (isEqual(road->GetEnd().pos, start, SENSITIVITY) && road->GetEnd().level == brushOnStart.GetLevel())
        {
            newRoad->connectStartToEndOf(road);
        }

        if (isEqual(road->GetEnd().pos, end, SENSITIVITY) && road->GetEnd().level == brushOnEnd.GetLevel())
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


