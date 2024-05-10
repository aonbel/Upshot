#include "graphicscene.h"

GraphicScene::GraphicScene() :
    numberOfLayers(1),
    layers(QVector<GraphicsLayer*>(numberOfLayers))
{

}

GraphicScene::GraphicScene(int _numberOfLayers) :
    numberOfLayers(_numberOfLayers),
    layers(QVector<GraphicsLayer*>(numberOfLayers))
{

}

void GraphicScene::AddItemOnLayer(QGraphicsItem* item, int layer)
{
    item->setParentItem(layers.at(layer));
    addItem(item);
}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit mouseEventOccured(mouseEvent);
}
