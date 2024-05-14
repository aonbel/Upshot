#ifndef INPUTPROCESSER_H
#define INPUTPROCESSER_H

#include <QtCore>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include "mymath.h"

const float DEFAULT_SEGMENT_LENGTH = 40;
const int MAX_LEVEL = 3;
const int MIN_LEVEL = 1;

class InputProcesser : public QObject
{
    Q_OBJECT
private:
    QPointF prevPos;
    int prevLevel;
    int currLevel;
public:
    InputProcesser();
    void ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent);
    void ProcessWheelEventByChangingLevel(QGraphicsSceneWheelEvent *wheelEvent);
    void ProcessKeyEventByChangingLevel(QKeyEvent *keyEvent);
    int GetLevel();
signals:
    void AnotherSegmentOccured(const QPointF& start, const QPointF& end, int startLevel, int endLevel);
};

#endif // INPUTPROCESSER_H
