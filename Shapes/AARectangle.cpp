#include "AARectangle.h"
#include "Utils.h"
#include <cmath>

AARectangle::AARectangle() : AARectangle(Vect2D::Zero, Vect2D::Zero)
{
}
AARectangle::AARectangle(const Vect2D& topLeft, unsigned int width, unsigned int heigth)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(Vect2D(topLeft.GetX() + width - 1, topLeft.GetY() + heigth - 1));
}

AARectangle::AARectangle(const Vect2D& topLeft, const Vect2D& bottomRight)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(bottomRight);
}

float AARectangle::GetWidth() const
{
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}

float AARectangle::GetHeigth() const
{
	return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY() + 1;
}



Vect2D AARectangle::GetCenterPoint() const
{
	return Vect2D(GetTopLeftPoint().GetX() + GetWidth() / 2.0f, GetTopLeftPoint().GetY() + GetHeigth() / 2.0f);
}

bool AARectangle::Intersects(const AARectangle& otherRect) const
{
	return !(otherRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() ||
			 otherRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX() ||
			 otherRect.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY() ||
			 otherRect.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY()    
			);
}
bool AARectangle::ContainsPoint(const Vect2D& point) const
{
	bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
	bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY();

	return withinX && withinY;
}

AARectangle AARectangle::Inset(const AARectangle& rect, Vect2D& insets)
{
	return AARectangle(rect.GetTopLeftPoint() + insets, rect.GetWidth() - 2 * insets.GetX(), rect.GetHeigth()- 2* insets.GetY());
}

vector<Vect2D> AARectangle::GetPoints() const
{
	vector<Vect2D> points;
	points.push_back(mPoints[0]);
	points.push_back(Vect2D(mPoints[1].GetX(), mPoints[0].GetY()));
	points.push_back(mPoints[1]);
	points.push_back(Vect2D(mPoints[0].GetX(), mPoints[1].GetY()));
	return points;
}

//my solution for function MoveTo(). Moves the center to the specified point

//void AARectangle::MoveTo(const Vect2D& newPosition)
//{
//	Vect2D centerPoint = GetCenterPoint();
//
//	float deltaX = newPosition.GetX() - centerPoint.GetX();
//	float deltaY = newPosition.GetY() - centerPoint.GetY();
//
//	mPoints[0] = Vect2D{ mPoints[0].GetX() + deltaX, mPoints[0].GetY() + deltaY };
//	mPoints[1] = Vect2D{ mPoints[1].GetX() + deltaX, mPoints[1].GetY() + deltaY };
//
//}

//Serge solution for function MoveTo(). Moves the top left corner to the specified point

void AARectangle::MoveTo(const Vect2D& position)
{
	float width = GetWidth();
	float heigth = GetHeigth();

	SetTopLeftPoint(position);
	SetBottomRightPoint(Vect2D(position.GetX() + width - 1, position.GetY() + heigth - 1));
}