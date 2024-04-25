#ifndef MOUSEPROCESSER_H
#define MOUSEPROCESSER_H

#include <QtCore>
#include <QGraphicsSceneMouseEvent>

#include "mymath.h"

class MouseProcesser : public QObject
{
    Q_OBJECT
private:
    QPointF prevPos;
    float segmentLength;
public:
    MouseProcesser();
    MouseProcesser(float segmentLength);
    void ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    void AnotherSegmentOccured(const QPointF& start, const QPointF& end);
};

#endif // MOUSEPROCESSER_H
