#include "helper.h"

/**
 * @brief Maps a input from one range to another range linearly
 * @param double input
 * @param double source input mininum range
 * @param double source input maximum range
 * @param double destination input minimum range
 * @param double destination input maximum range
 * @return double mapped input
 */
double linearMap(double input,
                 double srcMin,
                 double srcMax,
                 double dstMin,
                 double dstMax)
{
    return (((input-srcMin) / (srcMax-srcMin)) * (dstMax-dstMin) + dstMin);
}
