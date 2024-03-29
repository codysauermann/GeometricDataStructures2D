#include "SimplePoint2D.h"

SimplePoint2D::SimplePoint2D()
{
	this->x = "0";
	this->y = "0";
}

SimplePoint2D::SimplePoint2D(const SimplePoint2D& p)
{
	this->x = p.x;
	this->y = p.y;
}

SimplePoint2D::SimplePoint2D(Number x, Number y)
{
	this->x = x;
	this->y = y;
}

SimplePoint2D::SimplePoint2D(SimplePoint2D&& p)
{
	this->x = std::move(p.x);
	this->y = std::move(p.y);
}

SimplePoint2D& SimplePoint2D::operator=(const SimplePoint2D& p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}

SimplePoint2D& SimplePoint2D::operator=(SimplePoint2D&& p)
{
	this->x = std::move(p.x);
	this->y = std::move(p.y);
	return *this;
}

bool SimplePoint2D::operator<(const SimplePoint2D& p)
{
	if ((*this).x < p.x)
		return true;
	else
		return ((*this).x == p.x && (*this).y < p.y);
}

bool SimplePoint2D::operator<=(const SimplePoint2D& p)
{
	return (*this < p || *this == p);
}

bool SimplePoint2D::operator==(const SimplePoint2D& p)
{
	return ((*this).x == p.x && (*this).y == p.y);
}

bool SimplePoint2D::operator>=(const SimplePoint2D& p)
{
	return !((*this) < p);
}

bool SimplePoint2D::operator>(const SimplePoint2D& p)
{
	return !((*this) <= p);
}

bool SimplePoint2D::operator!=(const SimplePoint2D& p)
{
	return !((*this) == p);
}


SimplePoint2D& SimplePoint2D::operator=(SimplePoint2D&& p)
{
	this->x = std::move(p.x);
	this->y = std::move(p.y);
	return *this;
}
