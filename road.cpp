#include "road.h"

Road::Road(const QPointF &start, const QPointF &end, Road *_prev, Road *_next, TypeOfRoadDirection typeOfDir, NumberOfRoadLines numberOfLines, int level) :
    start(start),
    end(end),
    next(_next),
    prev(_prev),
    typeOfDir(typeOfDir),
    numberOfLines(numberOfLines),
    endsOfLines(new QVector<QPointF>),
    startsOfLines(new QVector<QPointF>),
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

    // IF BIDIRECTIONAL WE NEED TO REVERSE SOME EDGES

    if (typeOfDir == TypeOfRoadDirection::two_way)
    {
        QVector<QPointF> buffer;

        for (int i = 0;i<startsOfLines->count()/2;++i)
        {
            buffer.push_back(startsOfLines->back());
            startsOfLines->pop_back();
        }

        for (int i = 0;i<endsOfLines->count()/2;++i)
        {
            startsOfLines->push_back(endsOfLines->back());
            endsOfLines->pop_back();
        }

        for (auto edge : buffer)
        {
            endsOfLines->push_back(edge);
        }
    }
}

Road::Road(Road &obj) :
    start(obj.start),
    end(obj.end),
    typeOfDir(obj.typeOfDir),
    next(obj.next),
    prev(obj.prev),
    numberOfLines(obj.numberOfLines),
    startsOfLines(obj.startsOfLines),
    endsOfLines(obj.endsOfLines),
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
    startsOfLines(obj.startsOfLines),
    endsOfLines(obj.endsOfLines),
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

        endsOfLines->clear();

        float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

        QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

        QPointF endPos(rotationVector * WIDTH_OF_LINE / 2 + end);

        for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
        {
            endsOfLines->push_back(endPos);

            endPos -= WIDTH_OF_LINE * rotationVector;
        }

        return;
    }

    if (next == nullptr)
    {
        endsOfLines->clear();
        next = _next;
    }

    if (_next->level != level)
    {
        if (!endsOfLines->empty() || !_next->startsOfLines->empty())
        {
            return;
        }
    }

    for (auto start : _next->getStartsOfLines())
    {
        endsOfLines->push_back(start);
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

        startsOfLines->clear();

        float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

        QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

        QPointF startPos(rotationVector * WIDTH_OF_LINE / 2 + start);

        for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
        {
            startsOfLines->push_back(startPos);

            startPos -= WIDTH_OF_LINE * rotationVector;
        }

        return;
    }

    if (prev == nullptr)
    {
        startsOfLines->clear();
        prev = _prev;
    }

    if (_prev->level != level)
    {
        if (!startsOfLines->empty() || !_prev->endsOfLines->empty())
        {
            return;
        }
    }

    for (auto end : _prev->getEndsOfLines())
    {
        startsOfLines->push_back(end);
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

    size_t countOfEdges = std::max(startsOfLines->count(), endsOfLines->count());

    for (int iter = 0;iter<countOfEdges;iter++)
    {
        size_t firstIter = std::min(iter, startsOfLines->count() - 1);
        size_t secondIter = std::min(iter, endsOfLines->count() - 1);

        answer->push_back(Edge(startsOfLines->at(firstIter), endsOfLines->at(secondIter)));
    }

    return answer;
}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    auto edges = GetEdgesForGraph();

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

QVector<QPointF> Road::getEndsOfLines()
{
    return *endsOfLines;
}

QVector<QPointF> Road::getStartsOfLines()
{
    return *startsOfLines;
}

QPointF Road::GetStart() const
{
    return start;
}

QPointF Road::GetEnd() const
{
    return end;
}
