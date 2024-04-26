#include "mouseprocesser.h"

MouseProcesser::MouseProcesser() = default;

void MouseProcesser::ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF mousePos = mouseEvent->scenePos();

    if (mouseEvent->type() == QGraphicsSceneMouseEvent::GraphicsSceneMouseMove)
    {
        float dist = distanceBetweenQPoints(prevPos, mousePos);

        if (dist > 2 * DEFAULT_SEGMENT_LENGTH)
        {
            prevPos = mousePos;
        }
        else if (dist > DEFAULT_SEGMENT_LENGTH)
        {
            auto curr = prevPos + rotateVector(QPointF(DEFAULT_SEGMENT_LENGTH, .0F), vectorAngle(mousePos - prevPos));

            emit AnotherSegmentOccured(prevPos, curr);

            prevPos = curr;
        }
    }
}
