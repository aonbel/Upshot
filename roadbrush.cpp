#include "roadbrush.h"

RoadBrush::RoadBrush() :
    type(TypeOfRoadDirection::one_way),
    numberOfLines(NumberOfRoadLines::one_lane),
    level(1)
{

}

RoadBrush::RoadBrush(TypeOfRoadDirection _type, NumberOfRoadLines _numberOfLines, int _level) :
    type(_type),
    numberOfLines(_numberOfLines),
    level(_level)
{

}

void RoadBrush::SetType(TypeOfRoadDirection _type)
{
    type = _type;
}

void RoadBrush::SetNumberOfLines(NumberOfRoadLines _numberOfLines)
{
    numberOfLines = _numberOfLines;
}

void RoadBrush::SetLevel(int _level)
{
    level = _level;
}

TypeOfRoadDirection RoadBrush::GetType()
{
    return type;
}

NumberOfRoadLines RoadBrush::GetNumberOfLines()
{
    return numberOfLines;
}

int RoadBrush::GetLevel()
{
    return level;
}
