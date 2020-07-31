#include "Tetronimos.h"
#include "Screen.h"
#include "Excluder.h"


Tetronimos::Tetronimos() : mOutlineColor(Color::White()), mFillColor(Color::Blue())
{

}
void Tetronimos::Init(const AARectangle& rect, const AARectangle& boundary) //breakout.cpp

{
	Excluder::Init(rect);
	mTetrisBoundary = boundary; //boundary of the game
	mDirection = 0;
}

void Tetronimos::Update(uint32_t dt)
{
	Vect2D dir;
	if ((mDirection & tetronimosSpace::TetronimosDirection::LEFT) == tetronimosSpace::TetronimosDirection::LEFT && (mDirection & tetronimosSpace::TetronimosDirection::RIGHT) == tetronimosSpace::TetronimosDirection::RIGHT)
	{
		dir = Vect2D::Zero;
	}
	else if (mDirection == tetronimosSpace::TetronimosDirection::LEFT)
	{
		dir = LEFT_DIR;
	}
	else if (mDirection == tetronimosSpace::TetronimosDirection::RIGHT)
	{
		dir = RIGHT_DIR;
	}
	Vect2D dx = dir * LeftRightVELOCITY * MilliSecondsToSeconds(dt);

	MoveBy(dx); 

	const AARectangle& AATetronimos = GetAARectangle();

	if (!IsGreaterThanOrEqual(AATetronimos.GetBottomRightPoint().GetY(), mTetrisBoundary.GetBottomRightPoint().GetY()))
	{
		MoveBy(DOWN_DIR);
	}
	if (IsGreaterThanOrEqual(mTetrisBoundary.GetTopLeftPoint().GetX(), AATetronimos.GetTopLeftPoint().GetX()))
	{
		MoveTo(Vect2D(mTetrisBoundary.GetTopLeftPoint().GetX(), AATetronimos.GetTopLeftPoint().GetY()));
	}
	else if (IsGreaterThanOrEqual(AATetronimos.GetBottomRightPoint().GetX(), mTetrisBoundary.GetBottomRightPoint().GetX()))
	{
		MoveTo(Vect2D(mTetrisBoundary.GetBottomRightPoint().GetX() - AATetronimos.GetWidth(), AATetronimos.GetTopLeftPoint().GetY()));
	}
}
void Tetronimos::Draw(Screen& screen)
{
	screen.Draw(GetAARectangle(), mOutlineColor, true, mFillColor);// block.h
}
