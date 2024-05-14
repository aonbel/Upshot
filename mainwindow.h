#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "graphicscene.h"
#include "inputprocesser.h"
#include "roadcontainer.h"
#include "carsspawner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const int WINDOW_LENGTH = 2000;
const int WINDOW_WIDTH = 2000;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_TwoWayRoad_clicked();

    void on_radioButton_OneWayRoad_clicked();

    void on_radioButton_4LineRoad_clicked();

    void on_radioButton_2LineRoad_clicked();

    void on_radioButton_1LineRoad_clicked();

    void on_pushButton_Start_StopSim_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::MainWindow *ui;
    GraphicScene* graphicsScene;
    InputProcesser* inputProcesser;
    RoadContainer* roadContainer;
    CarsSpawner* carsSpawner;
    RoadBrush* brush;
    QTimer* mainTimer;
};
#endif // MAINWINDOW_H
