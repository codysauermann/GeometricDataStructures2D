#include "vector"
#include "utility"
#include "algorithm"
#include "queue"
#include "iostream"
#include "Region2D.h"
#include "HalfSegment2D.h"
#include "Segment2D.h"
#include <memory>
#include <iostream>

//Implementation
struct Region2D::Impl {
    Impl();
    Impl(std::vector<Segment2D> _regionSegments);
    Impl(const Region2D &region);
    ~Impl();

    std::vector<AttributedHalfSegment2D> regionSegments;
    std::vector<HalfSegment2D> halfSegments;
    std::vector<Segment2D> segments;

    void setFlags();
    SimplePoint2D GetDominatePoint(HalfSegment2D inputHalfSegment);
    HalfSegment2D GetBrotherSeg(HalfSegment2D currentHalfSeg);
    bool GetAboveFlag(HalfSegment2D currentHalfSeg);
    bool CheckLessThan(SimplePoint2D dp, HalfSegment2D halfSeg);
};


Region2D::Impl::Impl()
{
    std::vector<AttributedHalfSegment2D> empty;
    this->regionSegments = empty;
}
Region2D::Impl::~Impl() {}

Region2D::Impl::Impl(std::vector<Segment2D> _regionSegments)
{
    this->segments = _regionSegments;

    std::vector<HalfSegment2D> HalfSegVec; //temporary vector of half segments for later use
    for(int i = 0; i < _regionSegments.size(); i++)
    {
        HalfSegment2D domHalfSeg = HalfSegment2D(_regionSegments[i], true); //set dominant point half segment from segment
        HalfSegVec.push_back(domHalfSeg);
        HalfSegment2D endHalfSeg = HalfSegment2D(_regionSegments[i], false); //set end point half segment from segment
        HalfSegVec.push_back(endHalfSeg);
    }
    std::sort(HalfSegVec.begin(), HalfSegVec.end());

    this->halfSegments = HalfSegVec;
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

bool Region2D::Impl::CheckLessThan(SimplePoint2D dp, HalfSegment2D halfSeg)
{
    Segment2D seg = halfSeg.s;
    SimplePoint2D left = seg.leftEndPoint;
    SimplePoint2D right = seg.rightEndPoint;

    // handle infinite slope
    if (right.x == left.x) {
        return dp < left;
    }

    Number slope = (right.y - left.y) / (right.x - left.x);
    Number b = left.y - (slope * left.x);   // The minus '-' was originally a '/'. I think this is supposed to be based on y=mx+b, which rewrites into b=y-mx.
    Number halfSegY = (dp.x * slope) + b;

    return dp.y < halfSegY;
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
        currentHalfSeg = sweepQueue.front();
        sweepQueue.pop();

        if(currentHalfSeg.isDominatingPointLeft) {
            if(sweepStatus.empty())
            {
                sweepStatus.push_back(currentHalfSeg); //add half segment to sweep status at beginning
                regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg,true));
                regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), true));
            }
            else if(GetDominatePoint(currentHalfSeg) == GetDominatePoint(sweepStatus.back())) //add half segment to sweep status at end
            {
                sweepStatus.push_back(currentHalfSeg);
                regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg, !(GetAboveFlag(sweepStatus.back()))));
                regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), !(GetAboveFlag(sweepStatus.back()))));
            }
            else //add halfsegment to sweep status somewhere in the middle
            {
                int index = sweepStatus.size() - 1;
                while(!CheckLessThan(GetDominatePoint(currentHalfSeg), sweepStatus[index])) //find index
                {
                    index -= 1;
                }
                sweepStatus.emplace(sweepStatus.begin() + index, currentHalfSeg); //emplace at index
                regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg, !(GetAboveFlag(sweepStatus[index - 1]))));
                regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), !(GetAboveFlag(sweepStatus[index - 1]))));
            }
        }
        else {
            //remove halfsegment from status
            for(int  i = 0; i < sweepStatus.size(); i++)
            {
                if(sweepStatus[i].s == currentHalfSeg.s)
                {
                    sweepStatus.erase(sweepStatus.begin() + i);
                    break;
                }
            }
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

//destructor
Region2D::~Region2D() {}

//iterator methods
Region2D::iterator Region2D::begin()
{
    return this->pimpl->regionSegments.begin();
}
Region2D::iterator Region2D::end()
{
    return this->pimpl->regionSegments.end();
}

/*void Region2D::print()
{
    for (Segment2D s : this->getSegments())
        s.print();
}*/

std::vector<Segment2D> Region2D::getSegments()
{
    std::vector<Segment2D> segments;
    for (HalfSegment2D h : this->pimpl->halfSegments)
        if (h.isDominatingPointLeft)
            segments.push_back(h.s);
    return segments;
}

bool Region2D::operator==(const Region2D& other) const
{
    for (int i = 0; i < std::min(this->pimpl->halfSegments.size(), other.pimpl->halfSegments.size()); i++) {
        HalfSegment2D h1 = this->pimpl->halfSegments[i];
        HalfSegment2D h2 = other.pimpl->halfSegments[i];
        if (h1 != h2)
            return false;
    }
    return true;
}