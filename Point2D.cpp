#include "Point2D.h"
#include <algorithm>
#include <iostream>
using namespace std;


struct Point2D::Impl
{
    Impl(){};

    Impl(vector<SimplePoint2D> _pointCollection): pointCollection(move(_pointCollection)){};

    vector<SimplePoint2D> pointCollection;
    
    bool ordered;
};
Point2D::Point2D() {}


Point2D::Point2D(vector<SimplePoint2D> _pointCollection):pimpl(new Impl())
{
    _pointCollection.erase(unique(_pointCollection.begin(), _pointCollection.end()), _pointCollection.end());
    sort(_pointCollection.begin(), _pointCollection.end());
    this->pimpl->pointCollection = _pointCollection;
    this->pimpl->ordered = true;
}

Point2D::Point2D(vector<SimplePoint2D> _pointCollection, bool _ordered):pimpl(new Impl())
{
   this->pimpl->ordered = _ordered;
   if(_ordered){
        _pointCollection.erase(unique(_pointCollection.begin(), _pointCollection.end()), _pointCollection.end());
        sort(_pointCollection.begin(), _pointCollection.end());
   }
   this->pimpl->pointCollection = _pointCollection;
}

Point2D::Point2D(Point2D const &sourcePoint2D): pimpl(new Impl(*sourcePoint2D.pimpl))
{
}

Point2D::Point2D(Point2D &&sourcePoint2D)
{
    this->pimpl = move(sourcePoint2D.pimpl);
    sourcePoint2D.pimpl = nullptr;
}

Point2D::~Point2D(){}

int Point2D::count()
{
    return this->pimpl->pointCollection.size();
}

Point2D::Iterator Point2D::begin()
{
    return Iterator(&(this->pimpl->pointCollection)[0]);
}

Point2D::Iterator Point2D::end()
{
    return Iterator(&(this->pimpl->pointCollection)[this->pimpl->pointCollection.size()]);
}

/*Point2D randomPoint2D(long count, int minX, int maxX, int minY, int maxY)
{
    generateSeed();
    std::vector<SimplePoint2D> points;
    for (long i = 0; i < count; i++)
        points.push_back(randomSimplePoint2D(minX, maxX, minY, maxY));
    return Point2D(points);
}*/