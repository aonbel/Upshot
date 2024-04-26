#include "mouseprocesser.h"

MouseProcesser::MouseProcesser() = default;

MouseProcesser::MouseProcesser(float segmentLength) : segmentLength(segmentLength)
{

}

void MouseProcesser::ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF mousePos = mouseEvent->scenePos();

    if (mouseEvent->type() == QGraphicsSceneMouseEvent::GraphicsSceneMouseMove)
    {
        float dist = distanceBetweenQPoints(prevPos, mousePos);

        if (dist > 2 * segmentLength)
        {
            prevPos = mousePos;
        }
        else if (dist > segmentLength)
        {
            auto curr = prevPos + rotateVector(QPointF(segmentLength, .0F), vectorAngle(mousePos - prevPos));

            emit AnotherSegmentOccured(prevPos, curr);

            prevPos = curr;
        }
    }
}
