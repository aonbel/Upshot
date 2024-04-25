#include "road.h"

Road::Road(const QPointF &start, const QPointF &end, Road *prev, Road *next, TypeOfRoadDirection typeOfDir, NumberOfRoadLines numberOfLines) :
    start(start),
    end(end),
    prev(prev),
    next(next),
    typeOfDir(typeOfDir),
    numberOfLines(numberOfLines),
    endsOfLines(new QVector<QPointF>),
    startsOfLines(new QVector<QPointF>)
{
    float rotatedAngle = GetAngleOfTheRoad() + PI / 2;

    QPointF rotationVector(qCos(rotatedAngle), qSin(rotatedAngle));

    // PART WITH FINDING ENDS OF LINES

    if (next != nullptr)
    {
        *endsOfLines = *next->endsOfLines;
    }
    else
    {
        QPointF endPos(rotationVector * WIDTH_OF_LINE / 2 + end);

        for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
        {
            endsOfLines->push_back(endPos);

            endPos -= WIDTH_OF_LINE * rotationVector;
        }
    }

    // PART WITH FINDING STARTS OF LINES

    if (prev != nullptr)
    {
        *startsOfLines = *prev->endsOfLines;
    }
    else
    {
        QPointF startPos(rotationVector * WIDTH_OF_LINE / 2 + start);

        for (size_t currLine = 0; currLine < numberOfLines; ++currLine)
        {
            startsOfLines->push_back(startPos);

            startPos -= WIDTH_OF_LINE * rotationVector;
        }
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
    numberOfLines(obj.numberOfLines),
    startsOfLines(obj.startsOfLines),
    endsOfLines(obj.endsOfLines)
{

}

Road::Road(Road &&obj) noexcept :
    start(obj.start),
    end(obj.end),
    typeOfDir(obj.typeOfDir),
    numberOfLines(obj.numberOfLines),
    startsOfLines(obj.startsOfLines),
    endsOfLines(obj.endsOfLines)
{

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

/// REDO

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
