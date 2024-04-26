#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphicsScene(new GraphicScene)
    , mouseProcesser(new MouseProcesser())
    , roadContainer(new RoadContainer)
    , mainTimer(new QTimer)
{
    ui->setupUi(this);


    ui->mainScene->setScene(graphicsScene);
    graphicsScene->setSceneRect(0, 0, WINDOW_LENGTH, WINDOW_WIDTH);

    connect(graphicsScene, &GraphicScene::mouseEventOccured, mouseProcesser, &MouseProcesser::ProcessEventByDividingIntoSegments);
    connect(mouseProcesser, &MouseProcesser::AnotherSegmentOccured, roadContainer, &RoadContainer::AddRoad);
    connect(roadContainer, &RoadContainer::NewRoad, this, [this] (Road* newRoad)
    {
        graphicsScene->addItem(newRoad);
    });


    mainTimer->setInterval(TICK_TIME);
    connect(mainTimer, &QTimer::timeout, this, [this] ()
            {
                graphicsScene->update();
            });

    mainTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_StartSim_clicked()
{
    auto edges = roadContainer->GetGraph();

    disconnect(graphicsScene, &GraphicScene::mouseEventOccured, mouseProcesser, &MouseProcesser::ProcessEventByDividingIntoSegments);
    carsSpawner = new CarsSpawner(edges, graphicsScene);
}

