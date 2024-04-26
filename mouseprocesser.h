#ifndef MOUSEPROCESSER_H
#define MOUSEPROCESSER_H

#include <QtCore>
#include <QGraphicsSceneMouseEvent>

#include "mymath.h"

const float DEFAULT_SEGMENT_LENGTH = 40;

class MouseProcesser : public QObject
{
    Q_OBJECT
private:
    QPointF prevPos;
public:
    MouseProcesser();
    void ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    void AnotherSegmentOccured(const QPointF& start, const QPointF& end);
};

#endif // MOUSEPROCESSER_H
