#include "inputprocesser.h"

InputProcesser::InputProcesser()
{
    prevPos = QPointF();
    prevLevel = currLevel = MIN_LEVEL;
}

void InputProcesser::ProcessEventByDividingIntoSegments(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF mousePos = mouseEvent->scenePos();

    if (mouseEvent->type() == QGraphicsSceneMouseEvent::GraphicsSceneMouseMove) {
        float dist = vectorLength(prevPos - mousePos);

        if (dist > 1.5 * DEFAULT_SEGMENT_LENGTH) {
            prevPos = mousePos;
            prevLevel = currLevel;
        } else if (dist > DEFAULT_SEGMENT_LENGTH) {
            auto curr = prevPos
                        + rotateVector(QPointF(DEFAULT_SEGMENT_LENGTH, .0F),
                                       vectorAngle(mousePos - prevPos));

            emit AnotherSegmentOccured(prevPos, curr, prevLevel, currLevel);

            prevPos = curr;
            prevLevel = currLevel;
        }
    }
}

void InputProcesser::ProcessWheelEventByChangingLevel(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (wheelEvent->delta() > 0) {
        currLevel = std::min(currLevel + 1, MAX_LEVEL);
    }

    if (wheelEvent->delta() < 0) {
        currLevel = std::max(currLevel - 1, MIN_LEVEL);
    }
}

void InputProcesser::ProcessKeyEventByChangingLevel(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_E) {
        currLevel = std::min(currLevel + 1, MAX_LEVEL);
    }

    if (keyEvent->key() == Qt::Key_Q) {
        currLevel = std::max(currLevel - 1, MIN_LEVEL);
    }
}

int InputProcesser::GetLevel()
{
    return currLevel;
}
