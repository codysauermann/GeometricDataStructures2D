#include "Number.h"
#include "AttributedHalfSegment2D.h"
#include <climits>

AttributedHalfSegment2D::AttributedHalfSegment2D(HalfSegment2D hs, bool above)
{
	this->hs = hs;
	this->above = above;
}

AttributedHalfSegment2D::AttributedHalfSegment2D(const AttributedHalfSegment2D& ahs)
{
	this->hs = ahs.hs;
	this->above = ahs.above;
}

AttributedHalfSegment2D::AttributedHalfSegment2D(AttributedHalfSegment2D&& ahs)
{
	this->hs = std::move(ahs.hs);
	this->above = std::move(ahs.above);
}

void AttributedHalfSegment2D::operator=(const AttributedHalfSegment2D& ahs)
{
	this->hs.s = ahs.hs.s;
	this->hs.isDominatingPointLeft = ahs.hs.isDominatingPointLeft;
}

bool AttributedHalfSegment2D::operator==(const AttributedHalfSegment2D& ahs)
{
	return (this->hs.s == ahs.hs.s && this->hs.isDominatingPointLeft == ahs.hs.isDominatingPointLeft);
}

bool AttributedHalfSegment2D::operator>=(const AttributedHalfSegment2D& ahs)
{
	return !((*this) < ahs);
}

bool AttributedHalfSegment2D::operator>(const AttributedHalfSegment2D& ahs)
{
	return !((*this) <= ahs);
}

bool AttributedHalfSegment2D::operator<(const AttributedHalfSegment2D& ahs)
{
	return (this->hs < ahs.hs);
}

bool AttributedHalfSegment2D::operator<=(const AttributedHalfSegment2D& ahs)
{
	return (*this < ahs || *this == ahs);
}

bool AttributedHalfSegment2D::operator!=(const AttributedHalfSegment2D& ahs)
{
	return !((*this) == ahs);
}
