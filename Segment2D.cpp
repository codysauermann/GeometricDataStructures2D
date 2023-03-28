#include "Segment2D.h"
#include <cmath>

Segment2D::Segment2D()		// Created default constructor so that HalfSegment2D works.
{
}

Segment2D::Segment2D(const Segment2D& s)
{
	this->leftEndPoint = s.leftEndPoint;
	this->rightEndPoint = s.rightEndPoint;
}

Segment2D::Segment2D(SimplePoint2D l, SimplePoint2D r)
{
	if (l < r)
	{
		this->leftEndPoint = l;
		this->rightEndPoint = r;
	}
	else
	{
		this->leftEndPoint = r;
		this->rightEndPoint = l;
	}
}

Segment2D::Segment2D(Segment2D&& s)
{
	this->leftEndPoint = std::move(s.leftEndPoint);
	this->rightEndPoint = std::move(s.rightEndPoint);
}

Segment2D& Segment2D::operator=(const Segment2D& s)
{
	this->leftEndPoint = s.leftEndPoint;
	this->rightEndPoint = s.rightEndPoint;
	return *this;
}

Segment2D& Segment2D::operator=(Segment2D&& s)
{
	this->leftEndPoint = std::move(s.leftEndPoint);
	this->rightEndPoint = std::move(s.rightEndPoint);
	return *this;
}

bool Segment2D::operator==(const Segment2D& s)
{
	return (this->leftEndPoint == s.leftEndPoint && (*this).rightEndPoint == s.rightEndPoint);
	
}

bool Segment2D::operator>=(const Segment2D& s)
{
	return !((*this) < s);
}

bool Segment2D::operator>(const Segment2D& s)
{
	return !((*this) <= s);
}

bool Segment2D::operator<(const Segment2D& s)
{
	if (this->leftEndPoint < s.leftEndPoint)
		return true;
	else
		return (this->leftEndPoint == s.leftEndPoint && this->rightEndPoint < s.rightEndPoint);
}

bool Segment2D::operator<=(const Segment2D& s)
{
	return ((*this) < s || (*this) == s);
}

bool Segment2D::operator!=(const Segment2D& s)
{
	return !((*this) == s);
}

SimplePoint2D Segment2D::findIntersection(Segment2D s)
{
	Number x1 = leftEndPoint.x;
	Number y1 = leftEndPoint.y;
	Number x2 = rightEndPoint.x;
	Number y2 = rightEndPoint.y;
	Number x3 = s.leftEndPoint.x;
	Number y3 = s.leftEndPoint.y;
	Number x4 = s.rightEndPoint.x;
	Number y4 = s.rightEndPoint.y;

	Number denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
	SimplePoint2D empty;
	Number zero = "0.0";
	if (denominator == zero)
		return empty;
	else 
	{
		Number ia = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
		Number ib = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;
		Number one = "1.0";
		if (ia < zero || ia > one || ib < zero || ib > one) 
		{
			// The intersection point does not exist in at least one of the segments.
			return empty;
		} 
		else 
		{
			Number x = x1 + ia * (x2 - x1);
			Number y = y1 + ia * (y2 - y1);
			SimplePoint2D p(x, y);
			return p;
		}
	}
	return empty;
}