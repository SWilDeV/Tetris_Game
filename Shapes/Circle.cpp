#include "Circle.h"
#include "Utils.h"

Circle::Circle(): Circle(Vect2D::Zero, 0)
{
}
Circle::Circle(const Vect2D& center, float radius) : mRadius(radius)
{
	mPoints.push_back(center);
}

bool Circle::Intersects(const Circle& otherCircle) const
{
	return GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (mRadius + otherCircle.mRadius);
}
bool Circle::ContainsPoint(const Vect2D& point) const
{
	return IsLessThanOrEqual(GetCenterPoint().Distance(point), mRadius);
}