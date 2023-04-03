#ifndef LINE2D_H
#define LINE2D_H
#include "vector"
#include "HalfSegment2D.h"
#include "Segment2D.h"
#include <memory>
using namespace std;

class Line2D {
private:
     //vector to hold half segment data
     class Impl;
     unique_ptr<Impl> pimpl;
public:
    Line2D(); //empty constructor
    Line2D(std::vector<Segment2D> &inputLineSegments); //base constructor
    Line2D(const Line2D &sourceLine2D); //copy constructor
    Line2D(Line2D &&sourceLine2D); //move constructor
    ~Line2D(); //Destructor

    typedef std::vector<HalfSegment2D>::iterator iterator;
    iterator begin();
    iterator end();
};


#endif //LINE2D_H
