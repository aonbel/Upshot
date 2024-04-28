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
    RoadBrush(TypeOfRoadDirection _type, NumberOfRoadLines _numberOfLines, int _level);
    void SetType(TypeOfRoadDirection _type);
    void SetNumberOfLines(NumberOfRoadLines _numberOfLines);
    void SetLevel(int _level);
    TypeOfRoadDirection GetType();
    NumberOfRoadLines GetNumberOfLines();
    int GetLevel();
};

#endif // ROADBRUSH_H
