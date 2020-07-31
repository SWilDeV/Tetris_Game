#ifndef GAMES_BREAKOUT_PADDLE_H_
#define GAMES_BREAKOUT_PADDLE_H_

#include "Excluder.h"
#include <stdint.h>

class Screen;
class Ball;

namespace paddleSpace
{
	enum PaddleDirection
	{
		LEFT = 1 << 0,
		RIGHT = 1 << 1
	};
}


class Paddle : public Excluder
{
public:

	static const uint32_t PADDLE_WIDTH = 50;
	static const uint32_t PADDLE_HEIGHT = 10;
	void Init(const AARectangle& rect, const AARectangle& boundary);
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);
	bool Bounce(Ball& ball);

	inline bool IsMovingLeft() const { return mDirection == paddleSpace::PaddleDirection::LEFT; }
	inline bool IsMovingRight() const { return mDirection == paddleSpace::PaddleDirection::RIGHT; }
	
	//~00 -> 11
	// 0 | 1 = 1
	//0 & 1 = 0
	//1 & 1 = 1
	inline void SetMovementDirection(paddleSpace::PaddleDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(paddleSpace::PaddleDirection dir) { mDirection &= ~dir; }
	inline void StopMovement() { mDirection = 0; }


private:
	uint32_t mDirection; // direction we are moving
	AARectangle mBoundary; // boundary that the paddle is confined to
	const float VELOCITY = 300.0f; // 300 pixels per seconds
	const float CORNER_BOUNCE_AMT = 0.2f; // corner bounce amount


};

#endif // GAMES_BREAKOUT_PADDLE_H_


