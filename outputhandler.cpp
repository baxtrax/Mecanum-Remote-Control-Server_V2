#include "outputhandler.h"

OutputHandler::OutputHandler(QSlider *FRBL_topSliderRef,
                             QSlider *FRBL_botSliderRef,
                             QSlider *FLBR_topSliderRef,
                             QSlider *FLBR_botSliderRef)
{
    FRBL_topSlider = FRBL_topSliderRef;
    FRBL_botSlider = FRBL_botSliderRef;
    FLBR_topSlider = FLBR_topSliderRef;
    FLBR_botSlider = FLBR_botSliderRef;
}


/**
 * @brief Updates sliders on GUI to repersent FR/BL and FL/BR values. Function is
 * called any time a kinematics value is updated or changed.
 */
void OutputHandler::updateSliders(double FRBLSpeed, double FLBRSpeed)
{
    setFRBLSlider(FRBLSpeed);
    setFLBRSlider(FLBRSpeed);
}


//Setters
/**
 * @brief Sets value of FRBL slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void OutputHandler::setFRBLSlider(double value)
{
    double amplifiedFRBL = value * 100.0;
    if (amplifiedFRBL > 0.0) { // positive
        FRBL_botSlider->setValue(0.0);
        if (amplifiedFRBL <= IOConstants::MIN_SLIDER) {
            FRBL_topSlider->setValue(IOConstants::MIN_SLIDER);
        }  else {
            FRBL_topSlider->setValue(amplifiedFRBL);
        }
    } else if (amplifiedFRBL < 0.0) { // negative
        FRBL_topSlider->setValue(0.0);
        if (amplifiedFRBL >= -IOConstants::MIN_SLIDER) {
            FRBL_botSlider->setValue(-IOConstants::MIN_SLIDER);
        }  else {
            FRBL_botSlider->setValue(amplifiedFRBL);
        }
    } else { // zero
        FRBL_botSlider->setValue(0.0);
        FRBL_topSlider->setValue(0.0);
    }
}


/**
 * @brief Sets value of FLBR slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void OutputHandler::setFLBRSlider(double value)
{
    double amplifiedFLBR = value * 100.0;
    if (amplifiedFLBR > 0.0) { // positive
        FLBR_botSlider->setValue(0.0);
        if (amplifiedFLBR <= IOConstants::MIN_SLIDER) {
            FLBR_topSlider->setValue(IOConstants::MIN_SLIDER);
        }  else {
            FLBR_topSlider->setValue(amplifiedFLBR);
        }
    } else if (amplifiedFLBR < 0.0) { // negative
        FLBR_topSlider->setValue(0.0);
        if (amplifiedFLBR >= -IOConstants::MIN_SLIDER) {
            FLBR_botSlider->setValue(-IOConstants::MIN_SLIDER);
        }  else {
            FLBR_botSlider->setValue(amplifiedFLBR);
        }
    } else { // zero
        FLBR_botSlider->setValue(0.0);
        FLBR_topSlider->setValue(0.0);
    }
}
