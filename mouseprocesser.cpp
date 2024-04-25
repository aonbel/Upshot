#include "mouseprocesser.h"

MouseProcesser::MouseProcesser() = default;

MouseProcesser::MouseProcesser(float segmentLength) : segmentLength(segmentLength)
{

}

void MouseProcesser::ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->type() == QGraphicsSceneMouseEvent::GraphicsSceneMouseMove)
    {
        QPointF mousePos = mouseEvent->scenePos();
        float dist = distanceBetweenQPoints(prevPos, mousePos);
        if (isEqual(dist, segmentLength))
        {
            emit AnotherSegmentOccured(prevPos, mousePos);

            prevPos = mousePos;
        }
        else if (segmentLength < dist)
        {
            prevPos = mousePos;
        }
    }
}
