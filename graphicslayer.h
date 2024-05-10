#ifndef GRAPHICSLAYER_H
#define GRAPHICSLAYER_H

#include <QGraphicsItem>

class GraphicsLayer : public QGraphicsItem
{
public:
    GraphicsLayer();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;
    QRectF boundingRect() const override = 0;
};

#endif // GRAPHICSLAYER_H
