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
    graph->activeTheme()->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
    graph->axisX()->setSegmentCount(2);
    graph->axisY()->setSegmentCount(2);
    graph->axisZ()->setSegmentCount(2);
    graph->setSelectionMode(QAbstract3DGraph::SelectionNone);

    graph->axisX()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisX()->setMin(-SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisY()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisY()->setMin(0.0);
    graph->axisZ()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisZ()->setMin(-SimulationConstants::MAX_GRAPH_SIZE);

    QLinearGradient lightPinkBruise_Gradient(QPointF(0, 0), QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0xDD3CFD));
    lightPinkBruise_Gradient.setColorAt(1, QRgb(0xFF6F7A));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::LogicalMode);

    QLinearGradient darkUltramarine_Gradient(QPointF(0, 0),QPointF(1, 0));
    darkUltramarine_Gradient.setColorAt(0.0, QRgb(0x7517F8));
    darkUltramarine_Gradient.setColorAt(1.0, QRgb(0x02A4FF));
    darkUltramarine_Gradient.setCoordinateMode(QGradient::LogicalMode);

    QScatterDataProxy *FRBLDataProxy = new QScatterDataProxy();
    FRBLDataProxy->addItem(QScatterDataItem(QVector3D( //FR
        SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        SimulationConstants::BASE_LENGTH/2.0)));
    FRBLDataProxy->addItem(QScatterDataItem(QVector3D( //BL
        -SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        -SimulationConstants::BASE_LENGTH/2.0)));
    FRBLSeries = new QScatter3DSeries(FRBLDataProxy);
    FRBLSeries->setItemLabelVisible(false);
    FRBLSeries->setMesh(QAbstract3DSeries::MeshSphere);
    FRBLSeries->setItemSize(0.15f);
    FRBLSeries->setMeshSmooth(true);
    FRBLSeries->setBaseGradient(lightPinkBruise_Gradient);

    QScatterDataProxy *FLBRDataProxy = new QScatterDataProxy();
    FLBRDataProxy->addItem(QScatterDataItem(QVector3D( //FL
        -SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        SimulationConstants::BASE_LENGTH/2.0)));
    FLBRDataProxy->addItem(QScatterDataItem(QVector3D( //BR
        SimulationConstants::BASE_WIDTH/2.0,
        SimulationConstants::WHEEL_HEIGHT/2.0,
        -SimulationConstants::BASE_LENGTH/2.0)));

    FLBRSeries = new QScatter3DSeries(FLBRDataProxy);
    FLBRSeries->setMesh(QAbstract3DSeries::MeshSphere);
    FLBRSeries->setItemSize(0.15f);
    FLBRSeries->setMeshSmooth(true);
    FLBRSeries->setBaseGradient(darkUltramarine_Gradient);
    FLBRSeries->setItemLabelVisible(true);


    graph->addSeries(FRBLSeries);
    graph->addSeries(FLBRSeries);


    simulationWidget = QWidget::createWindowContainer(graph);


}

QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}
