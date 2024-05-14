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
    void setItemLayer(QGraphicsItem* item, int layer);
    void removeItemFromLayers(QGraphicsItem* item);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
    void keyPressEvent(QKeyEvent* keyEvent) override;
signals:
    void mouseEventOccured(QGraphicsSceneMouseEvent *mouseEvent);
    void wheelEventOccured(QGraphicsSceneWheelEvent *wheelEvent);
    void keyPressEventOccured(QKeyEvent* keyEvent);
};

#endif // GRAPHICSCENE_H
