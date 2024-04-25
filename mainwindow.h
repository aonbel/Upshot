#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "graphicscene.h"
#include "mouseprocesser.h"
#include "roadcontainer.h"
#include "carai.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_StartSim_clicked();

private:
    Ui::MainWindow *ui;
    GraphicScene* graphicsScene;
    MouseProcesser* mouseProcesser;
    RoadContainer* roadContainer;
    CarAI* carAI;
    QTimer* mainTimer;
};
#endif // MAINWINDOW_H
