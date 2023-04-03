#ifndef POINT2DIMPLR_H
#define POINT2DIMPLR_H
#include "Point2D.h"
#include <vector>

struct Point2DImplr : public Point2D
{
    vector<SimplePoint2D> getPoints();
};

#endif //POINT2DIMPLR_H
