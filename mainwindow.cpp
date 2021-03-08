#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtCharts::QSplineSeries *series1 = new QtCharts::QSplineSeries();
    QtCharts::QSplineSeries *series2 = new QtCharts::QSplineSeries();

    QtCharts::QCategoryAxis *axisX = new QtCharts::QCategoryAxis();
    QtCharts::QCategoryAxis *axisY = new QtCharts::QCategoryAxis();

    //Axis colors
    QPen axisYPen(QBrush(QRgb(0x5E5E6F)), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen axisXPen(QBrush(QRgb(0x303046)), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    //Axis Labels
    QFont axisLabelFont("Open Sans", 12);
    QBrush axisLabelPen(QRgb(0xA3A3AD));

    axisY->setLabelsFont(axisLabelFont);
    axisY->setLabelsBrush(axisLabelPen);
    axisY->setLinePen(axisYPen);
    axisY->setGridLinePen(axisXPen);

    //axisX->setLinePen(axisXPen);
    axisX->setGridLineVisible(false);

    //Axis data
    axisY->append("-1.00 ", -1.00);
    axisY->append("0 ", 0);
    axisY->append("1.00 ", 1.00);
    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axisY->setRange(-1.1, 1.1);

    axisX->setRange(0.7, 14.3);



    //Line colors
    QLinearGradient lightPinkBruise_Gradient;
    lightPinkBruise_Gradient.setStart(QPointF(0, 0));
    lightPinkBruise_Gradient.setFinalStop(QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0xDD3CFD));
    lightPinkBruise_Gradient.setColorAt(1.0, QRgb(0xFF6F7A));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QPen pen1(lightPinkBruise_Gradient, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QLinearGradient darkUltramarine_Gradient;
    lightPinkBruise_Gradient.setStart(QPointF(0, 0));
    lightPinkBruise_Gradient.setFinalStop(QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0x7517F8));
    lightPinkBruise_Gradient.setColorAt(1.0, QRgb(0x02A4FF));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QPen pen2(lightPinkBruise_Gradient, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    series1->setPen(pen1);
    series1->setName("spline");

    series2->setPen(pen2);
    series2->setName("spline");

    //TODO generate and append data dynamically

    //Series 2
    series1->append(1, -0.71);
    series1->append(2, -0.3);
    series1->append(3, 0.18);
    series1->append(4, 0.62);
    series1->append(5, 0.91);
    series1->append(6, 1);
    series1->append(7, 0.86);
    series1->append(8, 0.52);
    series1->append(9, 0.06);
    series1->append(10, -0.41);
    series1->append(11, -0.79);
    series1->append(12, -0.98);
    series1->append(13, -0.95);
    series1->append(14, -0.71);
    //Series 1
    series2->append(1, 0.71);
    series2->append(2, 0.95);
    series2->append(3, 0.98);
    series2->append(4, 0.79);
    series2->append(5, 0.41);
    series2->append(6, -0.06);
    series2->append(7, -0.52);
    series2->append(8, -0.86);
    series2->append(9, -1);
    series2->append(10, -0.91);
    series2->append(11, -0.62);
    series2->append(12, -0.18);
    series2->append(13, 0.3);
    series2->append(14, 0.71);


    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);

    // Attach data to axis after they have been configured and added
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);

    chart->setBackgroundVisible(false);

    // Removing unneeded space around chart
    chart->setMargins(QMargins(0, 0, 0, -20)); //-20 removes unnessary x-axis
    chart->setBackgroundRoundness(0);

    ui->kinematicsGraphView->setChart(chart);
    // Removes placeholder images
    ui->kinematicsGraphView->setStyleSheet(NULL);
    ui->simulationWidgetPlaceHolder->setStyleSheet(NULL);
    ui->kinematicsGraphView->setRenderHint(QPainter::Antialiasing);

    //3D Stuffs
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(scene);

    Qt3DCore::QEntity *cylinderEntity = new Qt3DCore::QEntity(scene);
    Qt3DExtras::QCylinderMesh *cylinderMesh = new Qt3DExtras::QCylinderMesh;
    cylinderMesh->setRadius(5);
    cylinderMesh->setLength(10);

    cylinderMesh->setRings(4);
    cylinderMesh->setSlices(10);

    //Transform cylinder
    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform;
    cylinderTransform->setScale3D(QVector3D(1, 1, 1)); //Keep scaled at typical for now
    cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));

    //Add configurations to cylinder
    cylinderEntity->addComponent(cylinderMesh);
    cylinderEntity->addComponent(cylinderTransform);
    cylinderEntity->addComponent(material);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(scene);
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
    cameraController->setCamera(camera);

    view->setRootEntity(scene);
    //view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x191932)));
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x05050f)));

    QWidget *container = QWidget::createWindowContainer(view);

    //Get rid of unnessary horizontal layout
    ui->simulationWidgetPlaceHolder->parentWidget()->layout()->replaceWidget(ui->simulationWidgetPlaceHolder, container);
}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

