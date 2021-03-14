#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <QObject>
#include <QDebug>
#include <QSlider>

#include "constants.h"

class OutputHandler : public QObject
{
    Q_OBJECT
public:
    OutputHandler(QSlider *FRBL_topSliderRef,
                  QSlider *FRBL_botSliderRef,
                  QSlider *FLBR_topSliderRef,
                  QSlider *FLBR_botSliderRef);
public slots:
    void updateSliders(double, double);
private:
    QSlider *FRBL_topSlider;
    QSlider *FRBL_botSlider;
    QSlider *FLBR_topSlider;
    QSlider *FLBR_botSlider;

    void setFRBLSlider(double value);
    void setFLBRSlider(double value);
};

#endif // OUTPUTHANDLER_H
