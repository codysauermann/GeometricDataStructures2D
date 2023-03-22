#ifndef HALFSEGMENT2D_H
#define HALFSEGMENT2D_H
#include "Segment2D.h"
struct HalfSegment2D
{
	Segment2D s;
	bool isDominatingPointLeft;
	HalfSegment2D();
	HalfSegment2D(const HalfSegment2D& hs);
	HalfSegment2D(Segment2D s, bool isLeft);
	HalfSegment2D(HalfSegment2D&& hs);
	HalfSegment2D& operator=(const HalfSegment2D& hs);
	HalfSegment2D& operator=(HalfSegment2D&& hs);
	bool operator<(const HalfSegment2D hs);
	bool operator<=(const HalfSegment2D hs);
	bool operator==(const HalfSegment2D hs);
	bool operator>=(const HalfSegment2D hs);
	bool operator>(const HalfSegment2D hs);
	bool operator!=(const HalfSegment2D hs);
	SimplePoint2D getDP();
};
#endif
