#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphicsScene(new GraphicScene)
    , mouseProcesser(new MouseProcesser(40))
    , roadContainer(new RoadContainer)
    , mainTimer(new QTimer)
{
    ui->setupUi(this);


    ui->mainScene->setScene(graphicsScene);
    graphicsScene->setSceneRect(0, 0, 2000, 2000);

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

    for (auto edge : *edges)
    {
        graphicsScene->addLine(QLineF(edge.startPos, edge.endPos), QPen(Qt::green));
        graphicsScene->addLine(QLineF(edge.endPos, edge.endPos), QPen(Qt::red, 4));
    }

    auto path = PathService::FindPath(PathService::FromEdgesToAdjMatrix(edges), edges->front().startPos, edges->back().endPos);

    if (path != nullptr)
    {
        carAI = new CarAI(path, new QVector<CarAI*>);

        graphicsScene->addItem(carAI->GetCar());
    }

    delete edges;
}

