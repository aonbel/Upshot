#include "graphicslayer.h"

GraphicsLayer::GraphicsLayer() = default;

void GraphicsLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF GraphicsLayer::boundingRect() const
{
    return {0, 0, 0, 0};
}
