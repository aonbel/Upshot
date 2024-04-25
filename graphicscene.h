#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPoint>
#include <QPointF>

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicScene();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
signals:
    void mouseEventOccured(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // GRAPHICSCENE_H
