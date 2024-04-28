#ifndef ROADBRUSH_H
#define ROADBRUSH_H

#include "road.h"

class RoadBrush
{
private:
    TypeOfRoadDirection type;
    NumberOfRoadLines numberOfLines;
    int level;
public:
    RoadBrush();
    RoadBrush(TypeOfRoadDirection type, NumberOfRoadLines numberOfLines, int level);
    void SetType(TypeOfRoadDirection type);
    void SetNumberOfLines(NumberOfRoadLines numberOfLines);
    void SetLevel(int level);
    TypeOfRoadDirection GetType();
    NumberOfRoadLines GetNumberOfLines();
    int GetLevel();
};

#endif // ROADBRUSH_H
