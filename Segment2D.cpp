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

void Segment2D::operator=(Segment2D s)
{
	this->leftEndPoint = s.leftEndPoint;
	this->rightEndPoint = s.rightEndPoint;
}

bool Segment2D::operator==(Segment2D s)
{
	return (this->leftEndPoint == s.leftEndPoint && (*this).rightEndPoint == s.rightEndPoint);
	
}

bool Segment2D::operator>=(const Segment2D s)
{
	return !((*this) < s);
}

bool Segment2D::operator>(const Segment2D s)
{
	return !((*this) <= s);
}

bool Segment2D::operator<(Segment2D s)
{
	if (this->leftEndPoint < s.leftEndPoint)
		return true;
	else
		return (this->leftEndPoint == s.leftEndPoint && this->rightEndPoint < s.rightEndPoint);
}

bool Segment2D::operator<=(Segment2D s)
{
	return ((*this) < s || (*this) == s);
}

bool Segment2D::operator!=(const Segment2D s)
{
	return !((*this) == s);
}
