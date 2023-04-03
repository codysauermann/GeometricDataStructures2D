#include "Point2DImplr.h"
vector<SimplePoint2D> Point2DImplr::getPoints()
{
    return Point2D::pimpl->pointCollection;
}