#include "roadbrush.h"

RoadBrush::RoadBrush() :
    type(TypeOfRoadDirection::one_way),
    numberOfLines(NumberOfRoadLines::one_lane),
    level(1)
{

}

RoadBrush::RoadBrush(TypeOfRoadDirection type, NumberOfRoadLines numberOfLines, int level) :
    type(type),
    numberOfLines(numberOfLines),
    level(level)
{

}

void RoadBrush::SetType(TypeOfRoadDirection type)
{
    type = type;
}

void RoadBrush::SetNumberOfLines(NumberOfRoadLines numberOfLines)
{
    numberOfLines = numberOfLines;
}

void RoadBrush::SetLevel(int level)
{
    level = level;
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
