#include "graphicscene.h"

GraphicScene::GraphicScene() = default;

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit mouseEventOccured(mouseEvent);
}
