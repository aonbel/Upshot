#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphicsScene(new GraphicScene(4))
    , inputProcesser(new InputProcesser)
    , roadContainer(new RoadContainer)
    , mainTimer(new QTimer)
    , brush(new RoadBrush)
    , carsSpawner(nullptr)
{
    ui->setupUi(this);

    ui->mainScene->setScene(graphicsScene);

    connect(graphicsScene,
            &GraphicScene::mouseEventOccured,
            inputProcesser,
            &InputProcesser::ProcessEventByDividingIntoSegments);

    connect(graphicsScene,
            &GraphicScene::wheelEventOccured,
            inputProcesser,
            &InputProcesser::ProcessWheelEventByChangingLevel);

    connect(graphicsScene,
            &GraphicScene::keyPressEventOccured,
            inputProcesser,
            &InputProcesser::ProcessKeyEventByChangingLevel);

    connect(inputProcesser,
            &InputProcesser::AnotherSegmentOccured,
            this,
            [this](const QPointF &start, const QPointF &end, int startLevel, int endLevel) {
                RoadBrush startBrush = *brush;
                RoadBrush endBrush = *brush;
                startBrush.SetLevel(startLevel);
                endBrush.SetLevel(endLevel);
                roadContainer->AddRoad(start, end, startBrush, endBrush);
            });

    connect(roadContainer, &RoadContainer::NewRoad, this, [this](Road *newRoad) {
        graphicsScene->setItemLayer(newRoad, newRoad->GetLevel());
    });

    connect(roadContainer, &RoadContainer::RemoveRoad, this, [this](Road *roadToRemove) {
        graphicsScene->removeItem(roadToRemove);
    });

    mainTimer->setInterval(TICK_TIME);
    connect(mainTimer, &QTimer::timeout, this, [this]() {
        graphicsScene->update();
        ui->label_CurrentLevel->setText(QString::number(inputProcesser->GetLevel()));
    });

    mainTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Start_StopSim_clicked()
{
    if (carsSpawner == nullptr) {
        auto edges = roadContainer->GetGraph();

        disconnect(graphicsScene,
                   &GraphicScene::mouseEventOccured,
                   inputProcesser,
                   &InputProcesser::ProcessEventByDividingIntoSegments);

        disconnect(graphicsScene,
                &GraphicScene::wheelEventOccured,
                inputProcesser,
                &InputProcesser::ProcessWheelEventByChangingLevel);

        disconnect(graphicsScene,
                &GraphicScene::keyPressEventOccured,
                inputProcesser,
                &InputProcesser::ProcessKeyEventByChangingLevel);

        carsSpawner = new CarsSpawner(edges, graphicsScene);

        delete edges;
    } else {
        delete carsSpawner;
        carsSpawner = nullptr;

        connect(graphicsScene,
                &GraphicScene::mouseEventOccured,
                inputProcesser,
                &InputProcesser::ProcessEventByDividingIntoSegments);

        connect(graphicsScene,
                &GraphicScene::wheelEventOccured,
                inputProcesser,
                &InputProcesser::ProcessWheelEventByChangingLevel);

        connect(graphicsScene,
                &GraphicScene::keyPressEventOccured,
                inputProcesser,
                &InputProcesser::ProcessKeyEventByChangingLevel);
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

void MainWindow::on_pushButton_Clear_clicked()
{
    if (carsSpawner != nullptr) {
        on_pushButton_Start_StopSim_clicked();
    }

    roadContainer->Clear();
}
