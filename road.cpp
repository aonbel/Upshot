#include "road.h"

Road::Road(const QPointF &start, const QPointF &end, Road *_prev, Road *_next, TypeOfRoadDirection typeOfDir, NumberOfRoadLines numberOfLines, int level) :
    start(start),
    end(end),
    next(_next),
    prev(_prev),
    typeOfDir(typeOfDir),
    numberOfLines(numberOfLines),
    endsOfLinesOnStart(new QVector<QPointF>),
    startsOfLinesOnStart(new QVector<QPointF>),
    endsOfLinesOnEnd(new QVector<QPointF>),
    startsOfLinesOnEnd(new QVector<QPointF>),
    level(level)
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    addNextRoad(next);
    addPrevRoad(prev);

    if (next != nullptr)
    {
        next->addPrevRoad(this);
    }

    if (prev != nullptr)
    {
        prev->addNextRoad(this);
    }
}

Road::Road(Road &obj) :
    start(obj.start),
    end(obj.end),
    typeOfDir(obj.typeOfDir),
    next(obj.next),
    prev(obj.prev),
    numberOfLines(obj.numberOfLines),
    endsOfLinesOnStart(new QVector<QPointF>),
    startsOfLinesOnStart(new QVector<QPointF>),
    endsOfLinesOnEnd(new QVector<QPointF>),
    startsOfLinesOnEnd(new QVector<QPointF>),
    level(obj.level)
{

}

Road::Road(Road &&obj) noexcept :
    start(obj.start),
    end(obj.end),
    next(obj.next),
    prev(obj.prev),
    typeOfDir(obj.typeOfDir),
    numberOfLines(obj.numberOfLines),
    endsOfLinesOnStart(new QVector<QPointF>),
    startsOfLinesOnStart(new QVector<QPointF>),
    endsOfLinesOnEnd(new QVector<QPointF>),
    startsOfLinesOnEnd(new QVector<QPointF>),
    level(obj.level)
{

}

void Road::addNextRoad(Road *_next)
{
    if (_next == nullptr)
    {
        if (next != nullptr)
        {
            return;
        }

        endsOfLinesOnEnd->clear();
        startsOfLinesOnEnd->clear();

        float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

        QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

        QPointF endPos((rotationVector * WIDTH_OF_LINE / 2) * (numberOfLines - 1) + end);

        if (typeOfDir == TypeOfRoadDirection::one_way)
        {
            for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
            {
                endsOfLinesOnEnd->push_back(endPos);

                endPos -= WIDTH_OF_LINE * rotationVector;
            }
        }
        else
        {
            for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
            {
                if (currLine < numberOfLines / 2)
                {
                    endsOfLinesOnEnd->push_back(endPos);
                }
                else
                {
                    startsOfLinesOnEnd->push_back(endPos);
                }

                endPos -= WIDTH_OF_LINE * rotationVector;
            }
        }

        return;
    }

    if (next == nullptr)
    {
        endsOfLinesOnEnd->clear();
        startsOfLinesOnEnd->clear();
        next = _next;
    }

    for (auto start : _next->getStartsOfLinesOnStart())
    {
        endsOfLinesOnEnd->push_back(start);
    }

    for (auto end : _next->getEndsOfLinesOnStart())
    {
        startsOfLinesOnEnd->push_back(end);
    }
}

void Road::addPrevRoad(Road *_prev)
{
    if (_prev == nullptr)
    {
        if (prev != nullptr)
        {
            return;
        }

        startsOfLinesOnStart->clear();
        endsOfLinesOnStart->clear();

        float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

        QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

        QPointF startPos((rotationVector * WIDTH_OF_LINE / 2) * (numberOfLines - 1) + start);

        if (typeOfDir == TypeOfRoadDirection::one_way)
        {
            for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
            {
                startsOfLinesOnStart->push_back(startPos);

                startPos -= WIDTH_OF_LINE * rotationVector;
            }
        }
        else
        {
            for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
            {
                if (currLine < numberOfLines / 2)
                {
                    startsOfLinesOnStart->push_back(startPos);
                }
                else
                {
                    endsOfLinesOnStart->push_back(startPos);
                }

                startPos -= WIDTH_OF_LINE * rotationVector;
            }
        }

        return;
    }

    if (prev == nullptr)
    {
        startsOfLinesOnStart->clear();
        endsOfLinesOnStart->clear();
        prev = _prev;
    }

    for (auto end : _prev->getEndsOfLinesOnEnd())
    {
        startsOfLinesOnStart->push_back(end);
    }

    for (auto start : _prev->getStartsOfLinesOnEnd())
    {
        endsOfLinesOnStart->push_back(start);
    }
}

float Road::GetAngleOfTheRoad() const
{
    QPointF direction = end - start;
    return qAtan2(direction.y(), direction.x());
}

QVector<Edge>* Road::GetEdgesForGraph() const
{
    QVector<Edge>* answer = new QVector<Edge>;

    for (auto start : *startsOfLinesOnStart)
    {
        for (auto end : *endsOfLinesOnEnd)
        {
            answer->push_back(Edge(start, end));
        }
    }

    for (auto start : *startsOfLinesOnEnd)
    {
        for (auto end : *endsOfLinesOnStart)
        {
            answer->push_back(Edge(start, end));
        }
    }

    return answer;
}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    auto edges = GetEdgesForGraph();

    if (edges == nullptr)
    {
        return;
    }

    for (auto edge: *edges)
    {
        QPointF* currPolygon = new QPointF[4];

        currPolygon[0] = edge.startPos + rotationVector * WIDTH_OF_LINE / 2;
        currPolygon[1] = edge.startPos - rotationVector * WIDTH_OF_LINE / 2;
        currPolygon[2] = edge.endPos - rotationVector * WIDTH_OF_LINE / 2;
        currPolygon[3] = edge.endPos + rotationVector * WIDTH_OF_LINE / 2;

        auto brush = QBrush();
        brush.setColor(Qt::lightGray);
        brush.setStyle(Qt::SolidPattern);

        painter->save();
        painter->setPen(QPen(Qt::lightGray));
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

    QPointF firstPnt = start - (rotationVector * WIDTH_OF_LINE / 2);
    QPointF secondPnt = start + (rotationVector * WIDTH_OF_LINE / 2);
    QPointF thirdPnt = end - (rotationVector * WIDTH_OF_LINE / 2);
    QPointF fourthPnt = end + (rotationVector * WIDTH_OF_LINE / 2);

    return QRectF(QPointF(std::min({firstPnt.x(), secondPnt.x(), thirdPnt.x(), fourthPnt.x()}), std::min({firstPnt.y(), secondPnt.y(), thirdPnt.y(), fourthPnt.y()})),
                  QPointF(std::max({firstPnt.x(), secondPnt.x(), thirdPnt.x(), fourthPnt.x()}), std::max({firstPnt.y(), secondPnt.y(), thirdPnt.y(), fourthPnt.y()})));
}

QVector<QPointF> Road::getEndsOfLinesOnStart()
{
    return *endsOfLinesOnStart;
}

QVector<QPointF> Road::getStartsOfLinesOnStart()
{
    return *startsOfLinesOnStart;
}

QVector<QPointF> Road::getEndsOfLinesOnEnd()
{
    return *endsOfLinesOnEnd;
}

QVector<QPointF> Road::getStartsOfLinesOnEnd()
{
    return *startsOfLinesOnEnd;
}

QPointF Road::GetStart() const
{
    return start;
}

QPointF Road::GetEnd() const
{
    return end;
}
