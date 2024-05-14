#include "graphicscene.h"

GraphicScene::GraphicScene() : GraphicScene(1)
{

}

GraphicScene::GraphicScene(int _numberOfLayers) :
    numberOfLayers(_numberOfLayers),
    layers(QVector<GraphicsLayer*>(numberOfLayers))
{
    for (int iter = 0;iter<_numberOfLayers;++iter)
    {
        layers[iter] = new GraphicsLayer;
        addItem(layers[iter]);
    }
}

void GraphicScene::setItemLayer(QGraphicsItem *item, int layer)
{
    item->setParentItem(layers[layer]);
}

void GraphicScene::removeItemFromLayers(QGraphicsItem *item)
{
    item->setParentItem(NULL);
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit mouseEventOccured(mouseEvent);
}

void GraphicScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    emit wheelEventOccured(wheelEvent);
}

void GraphicScene::keyPressEvent(QKeyEvent *keyEvent)
{
    emit keyPressEventOccured(keyEvent);
}
