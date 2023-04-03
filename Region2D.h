#ifndef REGION2D_H
#define REGION2D_H
#include "vector"
#include "utility"
#include "set"
#include "AttributedHalfSegment2D.h"
#include "Segment2D.h"
#include <memory>

class Region2D {
private:

    class Impl;

    std::unique_ptr<Impl> pimpl;

public:
    Region2D();
    ~Region2D();
    Region2D(std::vector<Segment2D> region);
    Region2D(Region2D const &region);
    Region2D(Region2D &&region);

    typedef std::vector<AttributedHalfSegment2D>::iterator iterator;
    iterator begin();
    iterator end();
    //void print();
    std::vector<Segment2D> getSegments();
    bool operator==(const Region2D& other) const;
};


#endif //REGION2D_H