#ifndef POINT2D_H
#define POINT2D_H
#include <vector>
#include "SimplePoint2D.h"
#include <memory>
using namespace std;


class Point2D {
private:
    class Impl;
    unique_ptr<Impl> pimpl;
    
public:
    Point2D();
    Point2D(vector<SimplePoint2D> _pointCollection);
    Point2D(Point2D const &sourcePoint2D);
    Point2D(Point2D &&sourcePoint2D);
    ~Point2D();

    typedef vector<SimplePoint2D>::iterator iterator;

    iterator begin();
    iterator end();

};

#endif //POINT2D_H
