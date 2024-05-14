#ifndef GRAPHICSLAYER_H
#define GRAPHICSLAYER_H

#include <QGraphicsItem>

class GraphicsLayer : public QGraphicsItem
{
public:
    GraphicsLayer();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // GRAPHICSLAYER_H
