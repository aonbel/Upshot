#ifndef ROADEDGE_H
#define ROADEDGE_H

#include "roadpoint.h"

struct RoadEdge
{
    RoadPoint startPos;
    RoadPoint endPos;

    RoadEdge() = default;

    RoadEdge(const RoadPoint& startPos, const RoadPoint& endPos) :
        startPos(startPos),
        endPos(endPos)
    {

    }

    RoadEdge(RoadPoint&& startPos, RoadPoint&& endPos) :
        startPos(startPos),
        endPos(endPos)
    {

    }

    void Reverse()
    {
        std::swap(startPos, endPos);
    }
};

#endif // ROADEDGE_H
