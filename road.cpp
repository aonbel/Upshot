#include "road.h"

Road::Road(const RoadPoint &start,
           const RoadPoint &end,
           TypeOfRoadDirection typeOfDir,
           NumberOfRoadLines numberOfLines)
    : start(start)
    , end(end)
    , next(nullptr)
    , prev(nullptr)
    , typeOfDir(typeOfDir)
    , numberOfLines(numberOfLines)
    , endsOfLinesOnStart(new QVector<RoadPoint>)
    , startsOfLinesOnStart(new QVector<RoadPoint>)
    , endsOfLinesOnEnd(new QVector<RoadPoint>)
    , startsOfLinesOnEnd(new QVector<RoadPoint>)
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    setDefaultEndsOnEnd();
    setDefaultEndsOnStart();
    setDefaultStartsOnEnd();
    setDefaultStartsOnStart();
}

Road::Road(Road &obj)
    : start(obj.start)
    , end(obj.end)
    , typeOfDir(obj.typeOfDir)
    , next(obj.next)
    , prev(obj.prev)
    , numberOfLines(obj.numberOfLines)
    , endsOfLinesOnStart(new QVector<RoadPoint>(*obj.endsOfLinesOnStart))
    , startsOfLinesOnStart(new QVector<RoadPoint>(*obj.startsOfLinesOnStart))
    , endsOfLinesOnEnd(new QVector<RoadPoint>(*obj.endsOfLinesOnEnd))
    , startsOfLinesOnEnd(new QVector<RoadPoint>(*obj.startsOfLinesOnEnd))
{}

Road::Road(Road &&obj) noexcept
    : start(obj.start)
    , end(obj.end)
    , next(obj.next)
    , prev(obj.prev)
    , typeOfDir(obj.typeOfDir)
    , numberOfLines(obj.numberOfLines)
    , endsOfLinesOnStart(obj.endsOfLinesOnStart)
    , startsOfLinesOnStart(obj.startsOfLinesOnStart)
    , endsOfLinesOnEnd(obj.endsOfLinesOnEnd)
    , startsOfLinesOnEnd(obj.startsOfLinesOnEnd)
{}

void Road::setDefaultStartsOnStart()
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    startsOfLinesOnStart->clear();
    startsOfLinesOnStartDef = true;

    QPointF startPos((rotationVector * WIDTH_OF_LINE / 2) * (numberOfLines - 1) + start.pos);

    if (typeOfDir == TypeOfRoadDirection::one_way) {
        for (size_t currLine = 0; currLine < numberOfLines; ++currLine) {
            startsOfLinesOnStart->push_back(RoadPoint(startPos, start.level));

            startPos -= WIDTH_OF_LINE * rotationVector;
        }
    } else {
        for (size_t currLine = 0; currLine < numberOfLines / 2; ++currLine) {
            startsOfLinesOnStart->push_back(RoadPoint(startPos, start.level));

            startPos -= WIDTH_OF_LINE * rotationVector;
        }
    }

    return;
}

void Road::setDefaultEndsOnStart()
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));
    endsOfLinesOnStart->clear();
    endsOfLinesOnStartDef = true;

    QPointF startPos((rotationVector * WIDTH_OF_LINE / 2) * (numberOfLines - 1) + start.pos);

    if (typeOfDir == TypeOfRoadDirection::two_way) {
        for (size_t currLine = 0; currLine < numberOfLines; ++currLine) {
            if (currLine >= numberOfLines / 2) {
                endsOfLinesOnStart->push_back(RoadPoint(startPos, start.level));
            }

            startPos -= WIDTH_OF_LINE * rotationVector;
        }
    }
}

void Road::setDefaultStartsOnEnd()
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));
    startsOfLinesOnEnd->clear();
    startsOfLinesOnEndDef = true;

    QPointF endPos((rotationVector * WIDTH_OF_LINE / 2) * (numberOfLines - 1) + end.pos);

    if (typeOfDir == TypeOfRoadDirection::two_way) {
        for (size_t currLine = 0; currLine < numberOfLines; ++currLine) {
            if (currLine >= numberOfLines / 2) {
                startsOfLinesOnEnd->push_back(RoadPoint(endPos, end.level));
            }

            endPos -= WIDTH_OF_LINE * rotationVector;
        }
    }
}

void Road::setDefaultEndsOnEnd()
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));
    endsOfLinesOnEnd->clear();
    endsOfLinesOnEndDef = true;

    QPointF endPos((rotationVector * WIDTH_OF_LINE / 2) * (numberOfLines - 1) + end.pos);

    if (typeOfDir == TypeOfRoadDirection::one_way) {
        for (size_t currLine = 0; currLine < numberOfLines; ++currLine) {
            endsOfLinesOnEnd->push_back(RoadPoint(endPos, end.level));

            endPos -= WIDTH_OF_LINE * rotationVector;
        }
    } else {
        for (size_t currLine = 0; currLine < numberOfLines / 2; ++currLine) {
            endsOfLinesOnEnd->push_back(RoadPoint(endPos, end.level));

            endPos -= WIDTH_OF_LINE * rotationVector;
        }
    }
}

void Road::connectStartToEndOf(Road *road)
{
    if (road == nullptr) {
        return;
    }

    if (startsOfLinesOnStartDef && road->getEndsOfLinesOnEnd().size()) {
        startsOfLinesOnStart->clear();
        startsOfLinesOnStartDef = false;
    }

    if (endsOfLinesOnStartDef && road->getStartsOfLinesOnEnd().size()) {
        endsOfLinesOnStart->clear();
        endsOfLinesOnStartDef = false;
    }

    for (auto end : road->getEndsOfLinesOnEnd()) {
        startsOfLinesOnStart->push_back(end);
    }

    for (auto start : road->getStartsOfLinesOnEnd()) {
        endsOfLinesOnStart->push_back(start);
    }
}

void Road::connectStartToStartOf(Road *road)
{
    if (road == nullptr) {
        return;
    }

    if (startsOfLinesOnStartDef && road->getEndsOfLinesOnStart().size()) {
        startsOfLinesOnStart->clear();
        startsOfLinesOnStartDef = false;
    }

    if (endsOfLinesOnStartDef && road->getStartsOfLinesOnStart().size()) {
        endsOfLinesOnStart->clear();
        endsOfLinesOnStartDef = false;
    }

    for (auto end : road->getEndsOfLinesOnStart()) {
        startsOfLinesOnStart->push_back(end);
    }

    for (auto start : road->getStartsOfLinesOnStart()) {
        endsOfLinesOnStart->push_back(start);
    }
}

void Road::connectEndToEndOf(Road *road)
{
    if (road == nullptr) {
        return;
    }

    if (startsOfLinesOnEndDef && road->getEndsOfLinesOnEnd().size()) {
        startsOfLinesOnEnd->clear();
        startsOfLinesOnEndDef = false;
    }

    if (endsOfLinesOnEndDef && road->getStartsOfLinesOnEnd().size()) {
        endsOfLinesOnEnd->clear();
        endsOfLinesOnEndDef = false;
    }

    for (auto end : road->getEndsOfLinesOnEnd()) {
        startsOfLinesOnEnd->push_back(end);
    }

    for (auto start : road->getStartsOfLinesOnEnd()) {
        endsOfLinesOnEnd->push_back(start);
    }
}

void Road::connectEndToStartOf(Road *road)
{
    if (road == nullptr) {
        return;
    }

    if (startsOfLinesOnEndDef && road->getEndsOfLinesOnStart().size()) {
        startsOfLinesOnEnd->clear();
        startsOfLinesOnEndDef = false;
    }

    if (endsOfLinesOnEndDef && road->getStartsOfLinesOnStart().size()) {
        endsOfLinesOnEnd->clear();
        endsOfLinesOnEndDef = false;
    }

    for (auto end : road->getEndsOfLinesOnStart()) {
        startsOfLinesOnEnd->push_back(end);
    }

    for (auto start : road->getStartsOfLinesOnStart()) {
        endsOfLinesOnEnd->push_back(start);
    }
}

float Road::GetAngleOfTheRoad() const
{
    QPointF direction = end.pos - start.pos;
    return qAtan2(direction.y(), direction.x());
}

QVector<RoadEdge> *Road::GetEdgesForGraph() const
{
    QVector<RoadEdge> *answer = new QVector<RoadEdge>;

    for (auto start : *startsOfLinesOnStart) {
        for (auto end : *endsOfLinesOnEnd) {
            answer->push_back(RoadEdge(start, end));
        }
    }

    for (auto start : *startsOfLinesOnEnd) {
        for (auto end : *endsOfLinesOnStart) {
            answer->push_back(RoadEdge(start, end));
        }
    }

    return answer;
}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    auto edges = GetEdgesForGraph();

    if (edges == nullptr) {
        return;
    }

    for (auto edge : *edges) {
        QPointF *currPolygon = new QPointF[4];

        currPolygon[0] = edge.startPos.pos + rotationVector * WIDTH_OF_LINE / 2;
        currPolygon[1] = edge.startPos.pos - rotationVector * WIDTH_OF_LINE / 2;
        currPolygon[2] = edge.endPos.pos - rotationVector * WIDTH_OF_LINE / 2;
        currPolygon[3] = edge.endPos.pos + rotationVector * WIDTH_OF_LINE / 2;

        auto brush = QBrush();
        brush.setColor(roadLevelColors[GetLevel()]);
        brush.setStyle(Qt::SolidPattern);

        painter->save();
        painter->setPen(QPen(roadLevelColors[GetLevel()]));
        painter->setBrush(brush);

        painter->drawPolygon(currPolygon, 4);

        painter->restore();
    }

    delete edges;
}

QRectF Road::boundingRect() const
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    QPointF firstPnt = start.pos - (rotationVector * WIDTH_OF_LINE / 2);
    QPointF secondPnt = start.pos + (rotationVector * WIDTH_OF_LINE / 2);
    QPointF thirdPnt = end.pos - (rotationVector * WIDTH_OF_LINE / 2);
    QPointF fourthPnt = end.pos + (rotationVector * WIDTH_OF_LINE / 2);

    return QRectF(QPointF(std::min({firstPnt.x(), secondPnt.x(), thirdPnt.x(), fourthPnt.x()}),
                          std::min({firstPnt.y(), secondPnt.y(), thirdPnt.y(), fourthPnt.y()})),
                  QPointF(std::max({firstPnt.x(), secondPnt.x(), thirdPnt.x(), fourthPnt.x()}),
                          std::max({firstPnt.y(), secondPnt.y(), thirdPnt.y(), fourthPnt.y()})));
}

QVector<RoadPoint> Road::getEndsOfLinesOnStart() const
{
    return *endsOfLinesOnStart;
}

QVector<RoadPoint> Road::getStartsOfLinesOnStart() const
{
    return *startsOfLinesOnStart;
}

QVector<RoadPoint> Road::getEndsOfLinesOnEnd() const
{
    return *endsOfLinesOnEnd;
}

QVector<RoadPoint> Road::getStartsOfLinesOnEnd() const
{
    return *startsOfLinesOnEnd;
}

RoadPoint Road::GetStart() const
{
    return start;
}

RoadPoint Road::GetEnd() const
{
    return end;
}

int Road::GetLevel() const
{
    return std::min(start.level, end.level);
}
