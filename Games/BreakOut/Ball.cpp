#include "Ball.h"
#include "Utils.h"
#include "Screen.h"
#include "Circle.h"
#include "BoundaryEdge.h"

const float Ball::RADIUS = 5.0f;

Ball::Ball():Ball(Vect2D::Zero, Ball::RADIUS)
{

}
Ball::Ball(const Vect2D& pos, float radius) : mBBox(pos-Vect2D(radius, radius), radius*2.0f , radius*2.0f ), mVelocity(Vect2D::Zero)
{

}

void Ball::Update(uint32_t dt)
{
	mBBox.MoveBy(mVelocity * MilliSecondsToSeconds(dt));
}

void Ball::Draw(Screen& screen)
{
	Circle circ = { mBBox.GetCenterPoint(), GetRadius() };
	screen.Draw(circ, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vect2D& pointOnEdge, bool limitToEdge) //I removed const before BoundaryEdge because it was creating a bug. Serge didn't
{
	if (edge.normal == DOWN_DIR)
	{
		mBBox.MoveTo(Vect2D(mBBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
	}
	else if (edge.normal == UP_DIR)
	{
		mBBox.MoveTo(Vect2D(mBBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBBox.GetHeigth()));
	}
	else if (edge.normal == RIGHT_DIR)
	{
		mBBox.MoveTo(Vect2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBBox.GetTopLeftPoint().GetY()));
	}
	else if(edge.normal == LEFT_DIR)
	{
		mBBox.MoveTo(Vect2D(edge.edge.GetP0().GetX() - mBBox.GetWidth(), mBBox.GetTopLeftPoint().GetY()));
	}

	pointOnEdge = edge.edge.ClosestPoint(mBBox.GetCenterPoint(), limitToEdge); 
}

void Ball::Bounce(const BoundaryEdge& edge)
{
	Vect2D pointOnEdge;
	MakeFlushWithEdge(edge, pointOnEdge, false);
	mVelocity = mVelocity.Reflect(edge.normal);
}


void Ball::MoveTo(const Vect2D& point)
{
	mBBox.MoveTo(point - Vect2D(GetRadius(), GetRadius()));
}