#include "helper.h"

/**
 * @brief Maps a input from one range to another range linearly
 * @param Input
 * @param Source input mininum range
 * @param Source input maximum range
 * @param Destination input minimum range
 * @param Destination input maximum range
 * @return Mapped input
 */
double linearMap(double input, double srcMin, double srcMax, double dstMin, double dstMax)
{
    return (((input - srcMin) / (srcMax - srcMin)) * (dstMax - dstMin) + dstMin);
}
