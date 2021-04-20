#include "simulationhandler.h"

//           | y+
//           |
//  x+       |
//  ---------+
//          /
//         /
//        / z+
//

SimulationHandler::SimulationHandler()
{

    Q3DScatter *graph = new Q3DScatter();
    graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    graph->scene()->activeCamera()->setCameraPosition(-135,22.5,160);
    graph->scene()->activeCamera()->setTarget(QVector3D(0,0,0));
    graph->activeTheme()->setType(Q3DTheme::ThemeUserDefined);
    graph->activeTheme()->setBackgroundEnabled(false);
    graph->activeTheme()->setWindowColor(QColor(5, 5, 15));
    graph->activeTheme()->setFont(QFont("Open Sans", 12));
    graph->activeTheme()->setLabelBackgroundEnabled(false);
    graph->activeTheme()->setLabelTextColor(QColor(QRgb(0xffffff)));
    graph->activeTheme()->setLightColor(QColor(QRgb(0xffffff)));
    graph->activeTheme()->setLightStrength(6.0f);
    graph->activeTheme()->setGridLineColor(QColor(QRgb(0xffffff)));
    graph->axisX()->setSegmentCount(2);
    graph->axisY()->setSegmentCount(2);
    graph->axisZ()->setSegmentCount(2);

    graph->axisX()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisX()->setMin(-SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisY()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisY()->setMin(0.0);
    graph->axisZ()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisZ()->setMin(-SimulationConstants::MAX_GRAPH_SIZE);

    //FR
    QScatterDataProxy *FRDataProxy = new QScatterDataProxy();
    FRDataProxy->addItem(QScatterDataItem(QVector3D(
        SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        SimulationConstants::BASE_LENGTH/2.0)));
    FRSeries = new QScatter3DSeries(FRDataProxy);
    FRSeries->setItemLabelFormat(QStringLiteral("FR - 1.0"));
    FRSeries->setMesh(QAbstract3DSeries::MeshSphere);
    FRSeries->setItemSize(0.15f);
    FRSeries->setMeshSmooth(true);

    //BL
    QScatterDataProxy *BLDataProxy = new QScatterDataProxy();
    BLDataProxy->addItem(QScatterDataItem(QVector3D(
        -SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        -SimulationConstants::BASE_LENGTH/2.0)));
    BLSeries = new QScatter3DSeries(BLDataProxy);
    BLSeries->setItemLabelFormat(QStringLiteral("BL - 1.0"));
    BLSeries->setMesh(QAbstract3DSeries::MeshSphere);
    BLSeries->setItemSize(0.15f);
    BLSeries->setMeshSmooth(true);

    //FL
    QScatterDataProxy *FLDataProxy = new QScatterDataProxy();
    FLDataProxy->addItem(QScatterDataItem(QVector3D(
        -SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        SimulationConstants::BASE_LENGTH/2.0)));

    FLSeries = new QScatter3DSeries(FLDataProxy);
    FLSeries->setItemLabelFormat(QStringLiteral("FL - 1.0"));
    FLSeries->setMesh(QAbstract3DSeries::MeshSphere);
    FLSeries->setItemSize(0.15f);
    FLSeries->setMeshSmooth(true);

    //BR
    QScatterDataProxy *BRDataProxy = new QScatterDataProxy();
    BRDataProxy->addItem(QScatterDataItem(QVector3D(
        SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        -SimulationConstants::BASE_LENGTH/2.0)));
    BRSeries = new QScatter3DSeries(BRDataProxy);
    BRSeries->setItemLabelFormat(QStringLiteral("BR - 1.0"));
    BRSeries->setMesh(QAbstract3DSeries::MeshSphere);
    BRSeries->setItemSize(0.15f);
    BRSeries->setMeshSmooth(true);



    graph->addSeries(FLSeries);
    graph->addSeries(BRSeries);
    graph->addSeries(FRSeries);
    graph->addSeries(BLSeries);


    simulationWidget = QWidget::createWindowContainer(graph);


}

QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}
