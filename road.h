#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

#include "roadedge.h"
#include "mymath.h"

const float WIDTH_OF_LINE = 20;

enum TypeOfRoadDirection
{
    one_way,
    two_way
};

enum NumberOfRoadLines
{
    one_lane = 1,
    two_lanes = 2,
    four_lanes = 4
};

const std::array<QColor, 4> roadLevelColors({ Qt::black, Qt::darkGray, Qt::gray, Qt::lightGray });

class Road : public QGraphicsItem
{
private:
    RoadPoint start;
    RoadPoint end;

    Road* prev;
    Road* next;

    TypeOfRoadDirection typeOfDir;
    NumberOfRoadLines numberOfLines;

    QVector<RoadPoint>* endsOfLinesOnStart;
    bool endsOfLinesOnStartDef;
    QVector<RoadPoint>* startsOfLinesOnStart;
    bool startsOfLinesOnStartDef;

    QVector<RoadPoint>* endsOfLinesOnEnd;
    bool endsOfLinesOnEndDef;
    QVector<RoadPoint>* startsOfLinesOnEnd;
    bool startsOfLinesOnEndDef;

public:
    Road(const RoadPoint& start, const RoadPoint& end, TypeOfRoadDirection typeOfDir, NumberOfRoadLines numberOfLines);
    Road(Road& obj);
    Road(Road&& obj) noexcept;

    void setDefaultStartsOnStart();
    void setDefaultEndsOnStart();
    void setDefaultStartsOnEnd();
    void setDefaultEndsOnEnd();

    void addNextRoad(Road *_next);
    void addPrevRoad(Road *_prev);

    void connectStartToEndOf(Road *road);
    void connectStartToStartOf(Road *road);
    void connectEndToEndOf(Road *road);
    void connectEndToStartOf(Road *road);

    float GetAngleOfTheRoad() const;

    QVector<RoadEdge>* GetEdgesForGraph() const;

    QVector<RoadPoint> getEndsOfLinesOnStart() const;
    QVector<RoadPoint> getStartsOfLinesOnStart() const;

    QVector<RoadPoint> getEndsOfLinesOnEnd() const;
    QVector<RoadPoint> getStartsOfLinesOnEnd() const;

    RoadPoint GetStart() const;
    RoadPoint GetEnd() const;
    int GetLevel() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // ROAD_H
