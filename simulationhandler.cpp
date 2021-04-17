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

    QtDataVisualization::Q3DScatter *graph = new QtDataVisualization::Q3DScatter();
    graph->setShadowQuality(QtDataVisualization::QAbstract3DGraph::ShadowQualitySoftLow);
    graph->scene()->activeCamera()->setCameraPreset(QtDataVisualization::Q3DCamera::CameraPresetIsometricRight);
    graph->scene()->activeCamera()->setZoomLevel(160);
    graph->activeTheme()->setType(QtDataVisualization::Q3DTheme::ThemeUserDefined);
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
    simulationWidget = QWidget::createWindowContainer(graph);


}

QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}
