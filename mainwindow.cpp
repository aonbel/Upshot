#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphicsScene(new GraphicScene)
    , mouseProcesser(new MouseProcesser())
    , roadContainer(new RoadContainer)
    , mainTimer(new QTimer)
    , brush(new RoadBrush)
    , carsSpawner(nullptr)
{
    ui->setupUi(this);

    ui->mainScene->setScene(graphicsScene);
    graphicsScene->setSceneRect(0, 0, WINDOW_LENGTH, WINDOW_WIDTH);

    connect(graphicsScene, &GraphicScene::mouseEventOccured, mouseProcesser, &MouseProcesser::ProcessEventByDividingIntoSegments);
    connect(mouseProcesser, &MouseProcesser::AnotherSegmentOccured, this, [this] (const QPointF& start, const QPointF& end)
            {
                roadContainer->AddRoad(start, end, *brush);
            });
    connect(roadContainer, &RoadContainer::NewRoad, this, [this] (Road* newRoad)
            {
                auto edges = newRoad->GetEdgesForGraph();

                graphicsScene->addItem(newRoad);

                for (auto edge : *edges)
                {
                    graphicsScene->addLine(QLineF(edge.startPos, edge.endPos), QPen(Qt::green, 1));
                }

                delete edges;
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

void MainWindow::on_pushButton_Start_StopSim_clicked()
{
    if (carsSpawner == nullptr)
    {
        auto edges = roadContainer->GetGraph();

        disconnect(graphicsScene, &GraphicScene::mouseEventOccured, mouseProcesser, &MouseProcesser::ProcessEventByDividingIntoSegments);

        carsSpawner = new CarsSpawner(edges, graphicsScene);

        delete edges;
    }
    else
    {
        delete carsSpawner;
        carsSpawner = nullptr;

        connect(graphicsScene, &GraphicScene::mouseEventOccured, mouseProcesser, &MouseProcesser::ProcessEventByDividingIntoSegments);
    }
}


void MainWindow::on_radioButton_TwoWayRoad_clicked()
{
    brush->SetType(TypeOfRoadDirection::two_way);
}


void MainWindow::on_radioButton_OneWayRoad_clicked()
{
    brush->SetType(TypeOfRoadDirection::one_way);
}


void MainWindow::on_radioButton_4LineRoad_clicked()
{
    brush->SetNumberOfLines(NumberOfRoadLines::four_lanes);
}


void MainWindow::on_radioButton_2LineRoad_clicked()
{
    brush->SetNumberOfLines(NumberOfRoadLines::two_lanes);
}


void MainWindow::on_radioButton_1LineRoad_clicked()
{
    brush->SetNumberOfLines(NumberOfRoadLines::one_lane);
}

