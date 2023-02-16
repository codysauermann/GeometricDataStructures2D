#ifndef ATTRIBUTEDHALFSEGMENT2D_H
#define ATTRIBUTEDHALFSEGMENT2D_H
#include "HalfSegment2D.h"
struct AttributedHalfSegment2D
{
	HalfSegment2D hs;
	bool above;
	AttributedHalfSegment2D(HalfSegment2D hs, bool above);
	AttributedHalfSegment2D(const AttributedHalfSegment2D& ahs);
	AttributedHalfSegment2D(AttributedHalfSegment2D&& ahs);
	void operator=(const AttributedHalfSegment2D ahs);
	bool operator<(const AttributedHalfSegment2D ahs);
	bool operator<=(const AttributedHalfSegment2D ahs);
	bool operator==(const AttributedHalfSegment2D ahs);
	bool operator>=(const AttributedHalfSegment2D ahs);
	bool operator>(const AttributedHalfSegment2D ahs);
	bool operator!=(const AttributedHalfSegment2D ahs);
};
#endif
