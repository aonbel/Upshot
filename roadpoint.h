#ifndef ROADPOINT_H
#define ROADPOINT_H

#include "mymath.h"

struct RoadPoint
{
    QPointF pos;
    int level;
    RoadPoint() = default;
    RoadPoint(QPointF pos, int level);
    RoadPoint(RoadPoint& point) = default;
    RoadPoint(const RoadPoint& point) = default;
    RoadPoint(RoadPoint&& point) = default;
    inline bool operator<(RoadPoint const& other) const
    {
        if (this->level != other.level)
        {
            return this->level < other.level;
        }

        auto firstLength = vectorLength(this->pos);
        auto secondLength = vectorLength(other.pos);

        if (isEqual(firstLength, secondLength))
        {
            auto firstAngle = vectorAngle(this->pos);
            auto secondAngle = vectorAngle(other.pos);

            return firstAngle < secondAngle;
        }
        else
        {
            return firstLength < secondLength;
        }
    }
    RoadPoint& operator=(const RoadPoint &other) = default;
    RoadPoint& operator=(RoadPoint &&other) = default;
    bool operator==(const RoadPoint &other) const;
    bool operator!=(const RoadPoint &other) const;
};

#endif // ROADPOINT_H
