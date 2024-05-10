#include "roadpoint.h"

RoadPoint::RoadPoint(QPointF pos, int level) :
    pos (pos),
    level (level)
{

}

bool RoadPoint::operator==(const RoadPoint &other) const
{
    return (this->pos == other.pos || pos == other.pos) && this->level == other.level;
}

bool RoadPoint::operator!=(const RoadPoint &other) const
{
    return this->pos != other.pos || this->level != other.level;
}
