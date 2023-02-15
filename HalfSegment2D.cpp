#include "Number.h"
#include "HalfSegment2D.h"
#include <climits>

HalfSegment2D::HalfSegment2D()		// Default Constructor so that AttributedHalfSegment2D works.
{
}

HalfSegment2D::HalfSegment2D(const HalfSegment2D& hs)
{
	this->s = hs.s;
	this->isDominatingPointLeft = hs.isDominatingPointLeft;
}

HalfSegment2D::HalfSegment2D(Segment2D s, bool isDominatingPointLeft)
{
	this->s = s;
	this->isDominatingPointLeft = isDominatingPointLeft;
}

HalfSegment2D::HalfSegment2D(HalfSegment2D&& hs)
{
	this->s = std::move(hs.s);
	this->isDominatingPointLeft = std::move(hs.isDominatingPointLeft);
}

void HalfSegment2D::operator=(HalfSegment2D hs)
{
	this->s = hs.s;
	this->isDominatingPointLeft = hs.isDominatingPointLeft;
}

bool HalfSegment2D::operator==(HalfSegment2D hs)
{
	return ((*this).s == hs.s && (*this).isDominatingPointLeft == hs.isDominatingPointLeft);
}

bool HalfSegment2D::operator>=(const HalfSegment2D hs)
{
	return !((*this) < hs);
}

bool HalfSegment2D::operator>(const HalfSegment2D hs)
{
	return !((*this) <= hs);
}

bool HalfSegment2D::operator<(HalfSegment2D hs)
{
	// Case 1: 
	if (this->getDP() < hs.getDP())
		return true;
	else if (this->getDP() > hs.getDP())
		return false;
	// if equal, move onto case 2a

	// Case 2a:
	if (!this->isDominatingPointLeft && hs.isDominatingPointLeft)			// this is right half segment and hs is left half segment
		return true;
	else if (!hs.isDominatingPointLeft && this->isDominatingPointLeft)		// this is left half segment and hs is right half segment
		return false;

	// Case 2b: 
	Number m1, m2;

	if (this->s.rightEndPoint.x == this->s.leftEndPoint.x)		// check for infinity slope
		m1 = INT_MAX;
	else
		m1 = (this->s.rightEndPoint.y - this->s.leftEndPoint.y) / (this->s.rightEndPoint.x - this->s.leftEndPoint.x);       // calculate slope of this normally

	if (hs.s.rightEndPoint.x == hs.s.leftEndPoint.x)		// check for infinity slope
		m2 = INT_MAX;
	else
		m2 = (hs.s.rightEndPoint.y - hs.s.leftEndPoint.y) / (hs.s.rightEndPoint.x - hs.s.leftEndPoint.x);					  // calculate slope of hs normally

	if (this->isDominatingPointLeft)                     		// both are left half segments
	{
		// so we are pretty much restricted to quadrants I and IV of the euclidean plane. Otherwise they could not both be left half segments.
		// this means we just need to compare slopes to check for the counterclockwise rotation
		if (m2 > m1)
			return true;
		else if (m1 > m2)
			return false;
		// if slope is equal, it is case 3
	}
	else                                  // both are right half segments - essentially opposite of if both are left
	{
		// so we are pretty much restricted to quadrants II and III of the euclidean plane. Otherwise they could not both be right half segments.
		// this means we just need to compare slopes to check for the counterclockwise rotation
		if (m2 > m1)
			return false;
		else if (m1 > m2)
			return true;
		// if slope is equal, it is case 3
	}

	// Calculate Lengths
	Number l1 = (this->s.rightEndPoint.y - this->s.leftEndPoint.y) * (this->s.rightEndPoint.y - this->s.leftEndPoint.y) + (this->s.rightEndPoint.x - this->s.leftEndPoint.x) * (this->s.rightEndPoint.x - this->s.leftEndPoint.x);
	Number l2 = (hs.s.rightEndPoint.y - hs.s.leftEndPoint.y) * (hs.s.rightEndPoint.y - hs.s.leftEndPoint.y) + (hs.s.rightEndPoint.x - hs.s.leftEndPoint.x) * (hs.s.rightEndPoint.x - hs.s.leftEndPoint.x);
	// Case 3:
	return (l1 < l2);
}

bool HalfSegment2D::operator<=(HalfSegment2D hs)
{
	return (*this < hs || *this == hs);
}

bool HalfSegment2D::operator!=(const HalfSegment2D hs)
{
	return !((*this) == hs);
}

SimplePoint2D HalfSegment2D::getDP()
{
	if(this->isDominatingPointLeft)
		return this->s.leftEndPoint;
	return this->s.rightEndPoint;
}

