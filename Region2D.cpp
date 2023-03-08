#include "vector"
#include "utility"
#include "algorithm"
#include "queue"
#include "iostream"
#include "Region2D.h"
#include "HalfSegment2D.h"
#include "Segment2D.h"
#include <memory>

//Implementation
struct Region2D::Impl {
    Impl();
    Impl(std::vector<Segment2D> _regionSegments);
    Impl(const Region2D &region);
    ~Impl();

    std::vector<AttributedHalfSegment2D> regionSegments;
    std::vector<HalfSegment2D> halfSegments;

    void setFlags();
    SimplePoint2D GetDominatePoint(HalfSegment2D inputHalfSegment);
    HalfSegment2D GetBrotherSeg(HalfSegment2D currentHalfSeg);
    bool GetAboveFlag(HalfSegment2D currentHalfSeg);
    //void setFlagsInCycle(std::vector<HalfSegment2D> cycle);
};


Region2D::Impl::Impl()
{
    std::vector<AttributedHalfSegment2D> empty;
    this->regionSegments = empty;
}
Region2D::Impl::~Impl() {}

Region2D::Impl::Impl(std::vector<Segment2D> _regionSegments)
{
    std::vector<HalfSegment2D> HalfSegVec; //temporary vector of half segments for later use
    //_regionSegments.erase(unique(_regionSegments.begin(), _regionSegments.end()), _regionSegments.end()); //remove any duplicate segments
    for(int i = 0; i < _regionSegments.size(); i++)
    {
        HalfSegment2D domHalfSeg = HalfSegment2D(_regionSegments[i], true); //set dominant point half segment from segment
        HalfSegVec.push_back(domHalfSeg);
        HalfSegment2D endHalfSeg = HalfSegment2D(_regionSegments[i], false); //set end point half segment from segment
        HalfSegVec.push_back(endHalfSeg);
    }
    std::sort(HalfSegVec.begin(), HalfSegVec.end());


    this->halfSegments = HalfSegVec;
    setFlags();
}

SimplePoint2D Region2D::Impl::GetDominatePoint(HalfSegment2D inputHalfSegment)
{
    Segment2D tempSegment = inputHalfSegment.s;
    if(inputHalfSegment.isDominatingPointLeft)
    {
        return tempSegment.leftEndPoint;
    }
    else {
        return tempSegment.rightEndPoint;
    }
}

HalfSegment2D Region2D::Impl::GetBrotherSeg(HalfSegment2D currentHalfSeg)
{
    HalfSegment2D brotherSeg  = currentHalfSeg;
    brotherSeg.isDominatingPointLeft = !currentHalfSeg.isDominatingPointLeft;
    return brotherSeg;
}

bool Region2D::Impl::GetAboveFlag(HalfSegment2D currentHalfSeg)
{
    for(int i = 0; i < regionSegments.size(); i++) {
        if(regionSegments[i].hs == currentHalfSeg)
        {
            return regionSegments[i].above;
        }
    }
}

void Region2D::Impl::setFlags()
{
    //initializing sweep structures
    std::queue<HalfSegment2D> sweepQueue;
    std::vector<HalfSegment2D> sweepStatus;

    for(int i = 0; i < halfSegments.size(); i++) //loading queue with half segments for sweep
    {
        sweepQueue.push(halfSegments[i]);
    }

    HalfSegment2D currentHalfSeg;

    while(!sweepQueue.empty())
    {
        if(sweepStatus.empty())
        {
            sweepStatus.push_back(currentHalfSeg); //add half segment to sweep status at beginning
            regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg,true));
            regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), true));
        }
        else if(GetDominatePoint(currentHalfSeg) == GetDominatePoint(sweepStatus.back())) 
        {
            sweepStatus.push_back(currentHalfSeg);
            regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg, !(GetAboveFlag(sweepStatus.back()))));
            regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), !(GetAboveFlag(sweepStatus.back()))));
        }
        else
        {
            //use slope to find location in sweep status
        }
    }
}



///////////////////////////////////////////////////////// Region Constructors ///////////////////////////////////////////////////////////////////////////////////

Region2D::Impl::Impl(const Region2D &region)
{
    this->regionSegments = region.pimpl->regionSegments;
}

//empty constructor
Region2D::Region2D() : pimpl(new Impl) {}

//copy constructor
Region2D::Region2D(Region2D const &region) : pimpl(new Impl(region)) {}

//base constructor
Region2D::Region2D(std::vector<Segment2D> region) : pimpl(new Impl(region)) {}

//move constructor
Region2D::Region2D(Region2D &&region) : pimpl(std::move(region.pimpl)) {}

