#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPoint>
#include <QPointF>
#include "graphicslayer.h"

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
    int numberOfLayers;
    QVector<GraphicsLayer*> layers;
public:
    GraphicScene();
    explicit GraphicScene(int _numberOfLayers);
    void AddItemOnLayer(QGraphicsItem* item, int layer);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
signals:
    void mouseEventOccured(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // GRAPHICSCENE_H
