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


    void GetCyclicData();
    SimplePoint2D GetDominatePoint(HalfSegment2D inputHalfSegment);
    HalfSegment2D GetNextHalfSegCounterClock(HalfSegment2D currentHalfSeg);
    HalfSegment2D GetBrotherSeg(HalfSegment2D currentHalfSeg);
    HalfSegment2D GetNextHalfSegClock(HalfSegment2D currentHalfSeg);
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
    try
    {
        GetCyclicData();
    }
    catch (...) {
        std::cout << "Input Segments Don't Form a Valid Region" << std::endl;
    }
    sort(regionSegments.begin(), regionSegments.end());
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

HalfSegment2D Region2D::Impl::GetNextHalfSegClock(HalfSegment2D currentHalfSeg)
{
    HalfSegment2D nextHalfSeg;
    for(int i = halfSegments.size(); i >= 0; i--)
    {
        if(GetDominatePoint(currentHalfSeg) == GetDominatePoint(halfSegments[i]))
        {
            nextHalfSeg = halfSegments[i];
            break;
        }
    }
    return nextHalfSeg;
}

HalfSegment2D Region2D::Impl::GetNextHalfSegCounterClock(HalfSegment2D currentHalfSeg)
{
    HalfSegment2D nextHalfSeg;
    for(int i = 0; i < halfSegments.size(); i++)
    {
        if(GetDominatePoint(currentHalfSeg) == GetDominatePoint(halfSegments[i]))
        {
            nextHalfSeg = halfSegments[i];
            break;
        }
    }
    return nextHalfSeg;
}

void Region2D::Impl::GetCyclicData()
{
    //initializing sweep structures
    std::queue<HalfSegment2D> sweepQueue;
    std::vector<HalfSegment2D> sweepStatus;

    for(int i = 0; i < halfSegments.size(); i++) //loading queue with half segments for sweep
    {
        sweepQueue.push(halfSegments[i]);
    }
    std::vector<HalfSegment2D> annotated; //will contain every half segment that has been visited/annotated
    std::vector<SimplePoint2D> visitedDP; //will contain every visited dominate point
    int walkAdjacency; //will be used to tell cycle walk which adjacency to use

    HalfSegment2D currentHalfSeg;

    while(!sweepQueue.empty()) //while not end of sweep
    {
        //moving current segment from queue to sweep status and adjusting accordingly
        currentHalfSeg = sweepQueue.front();
        if(currentHalfSeg.isDominatingPointLeft) //adding segment to sweep status
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
                int i = sweepStatus.size() - 1;
                while(GetDominatePoint(currentHalfSeg).y < GetDominatePoint(sweepStatus[i]).y)
                {
                    i -= 1;
                    if(i == -1) {
                        break;
                    }
                }
                while(GetDominatePoint(currentHalfSeg).y < GetDominatePoint(GetBrotherSeg(sweepStatus[i])).y)
                {
                    i -= 1;
                    if(i == -1) {
                        break;
                    }
                }
                sweepStatus.emplace(sweepStatus.begin() + (i + 1), currentHalfSeg);
                if(sweepStatus.front() == currentHalfSeg)
                {
                    regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg, true));
                    regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), true));
                }
                else
                {
                    regionSegments.push_back(AttributedHalfSegment2D(currentHalfSeg, !(GetAboveFlag(sweepStatus[i]))));
                    regionSegments.push_back(AttributedHalfSegment2D(GetBrotherSeg(currentHalfSeg), !(GetAboveFlag(sweepStatus[i]))));
                }
            }
        }
        else { //removing element from sweep status
            HalfSegment2D temp = HalfSegment2D(currentHalfSeg.s, true);
            sweepStatus.erase(find(sweepStatus.begin(), sweepStatus.end(), temp)); //remove segment from sweep status once end of it is reached
        }
        sweepQueue.pop(); //removing current half segment from queue

        if(find(annotated.begin(), annotated.end(), currentHalfSeg) != annotated.end()) //if segment is already visited continue
        {
            continue;
        }
        else
        {
            std::vector<HalfSegment2D> currentCycle; // will contain all half segments in current cycle
            currentCycle.push_back(currentHalfSeg); //add currently unannotated half segment to new cycle
            currentCycle.push_back(GetBrotherSeg(currentHalfSeg)); //add brother to current half segment to current cycle
            visitedDP.push_back(GetDominatePoint(currentHalfSeg)); //add new segments DP to visited (Visitdp(c))
            annotated.push_back(currentHalfSeg); // add current half segment to annotated
            annotated.push_back(GetBrotherSeg(currentHalfSeg));  //add brother to annotated/visited

            HalfSegment2D nextHalfSeg;
            HalfSegment2D prevHalfSeg = sweepStatus[find(sweepStatus.begin(), sweepStatus.end(), currentHalfSeg) - sweepStatus.begin() - 1];
            if(find(regionSegments.begin(), regionSegments.end(), AttributedHalfSegment2D(prevHalfSeg, true)) != regionSegments.end()) //if current half segment belongs to a hole
            {
                //getting h+ from c counterclockwise adjacency
                nextHalfSeg = GetNextHalfSegCounterClock(GetBrotherSeg(currentHalfSeg));
                walkAdjacency = 0;
            }
            else
            {
                //getting h+ from c clockwise adjacency
                nextHalfSeg = GetNextHalfSegClock(GetBrotherSeg(currentHalfSeg));
                walkAdjacency = 1;
            }

            while(!(currentHalfSeg == nextHalfSeg))
            {

                if(std::find(visitedDP.begin(), visitedDP.end(), GetDominatePoint(nextHalfSeg)) != visitedDP.end()) //if visitedDP(c)
                {
                    HalfSegment2D q = nextHalfSeg;
                    nextHalfSeg = GetNextHalfSegCounterClock(nextHalfSeg);
                    while(!(GetDominatePoint(nextHalfSeg) == GetDominatePoint(q))) //cycle backwards to anchor point (dp(q))
                    {
                        annotated.pop_back(); //remove current half segment from annotated list
                        annotated.pop_back(); //remove current brother segment from annotated list
                        nextHalfSeg = GetNextHalfSegCounterClock(nextHalfSeg);
                    }
                    nextHalfSeg = q;
                }
                else
                {
                    currentCycle.push_back(nextHalfSeg); //add current half seg to current cycle
                    visitedDP.push_back(GetDominatePoint(nextHalfSeg)); //visit current DP
                    HalfSegment2D brotherHalfSeg = GetBrotherSeg(nextHalfSeg); // get brother half seg
                    currentCycle.push_back(brotherHalfSeg); // add brother to current cycle
                    annotated.push_back(nextHalfSeg);
                    annotated.push_back(brotherHalfSeg);
                    if(walkAdjacency == 0) //counterclockwise adjacency
                    {
                        nextHalfSeg = GetNextHalfSegCounterClock(brotherHalfSeg);
                    }
                    else
                    {
                        nextHalfSeg = GetNextHalfSegClock(brotherHalfSeg);
                    }
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

