#include "Line2D.h"
#include "vector"
#include "HalfSegment2D.h"
#include "utility"
#include <algorithm>
using namespace std;


struct Line2D::Impl
{
    Impl(){};

    Impl(vector<Segment2D> inputLineSegments){};

    vector<HalfSegment2D> lineSegments;

    void CheckForIntersection();

};
//empty constructor
Line2D::Line2D() {}

//base constructor
Line2D::Line2D(std::vector<Segment2D> &inputLineSegments): pimpl(new Impl())
{
    //std::sort(inputLineSegments.begin(), inputLineSegments.end()); //sort input vector to order segments
    inputLineSegments.erase(unique(inputLineSegments.begin(), inputLineSegments.end()), inputLineSegments.end()); //remove any duplicate segments
    for(int i = 0; i < inputLineSegments.size(); i++)
    {
        HalfSegment2D domHalfSeg = HalfSegment2D(inputLineSegments[i], true); //set dominant point half segment from segment
        this->pimpl->lineSegments.push_back(domHalfSeg);
        HalfSegment2D endHalfSeg = HalfSegment2D(inputLineSegments[i], false); //set end point half segment from segment
        this->pimpl->lineSegments.push_back(endHalfSeg);
    }
    sort(this->pimpl->lineSegments.begin(), this->pimpl->lineSegments.end());
}

//copy constructor
Line2D::Line2D(const Line2D &sourceLine2D): pimpl(new Impl(*sourceLine2D.pimpl))
{

}

//move constructor
Line2D::Line2D(Line2D &&sourceLine2D)
{
 this->pimpl = move(sourceLine2D.pimpl);
 sourceLine2D.pimpl = nullptr;
}

//destructor
Line2D::~Line2D(){}

Line2D::iterator Line2D::begin()
{
    return this->pimpl->lineSegments.begin();
}
Line2D::iterator Line2D::end()
{
    return this->pimpl->lineSegments.end();
}