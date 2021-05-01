#include "helper.h"

double linearMap(double input, double srcMin, double srcMax, double dstMin, double dstMax)
{
    return (((input-srcMin) / (srcMax-srcMin)) * (dstMax-dstMin) + dstMin);
}
