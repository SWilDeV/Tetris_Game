#ifndef GAMES_BREAKOUT_LEVELBOUNDARY_H_
#define GAMES_BREAKOUT_LEVELBOUNDARY_H_

#include "Excluder.h"
#include "AARectangle.h"

class AARectangle;
class Ball;

class LevelBoundary
{
public:
	LevelBoundary() {}
	LevelBoundary(const AARectangle& boundary);
	bool HasCollided(const Ball& ball, BoundaryEdge& edge);
	const AARectangle& GetAARectangle() const { return mIncluder.GetAARectangle(); }


private:

	bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const; // check if we have collided
	Excluder mIncluder;
};
#endif // !GAMES_BREAKOUT_LEVELBOUNDARY_H_

