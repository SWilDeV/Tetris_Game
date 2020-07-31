#ifndef GAMES_TETRIS_TETRONIMOS_H_
#define GAMES_TETRIS_TETRONIMOS_H_

#include "AARectangle.h"
#include <stdint.h>
#include "BoundaryEdge.h"
#include "Shapes.h"
#include "Excluder.h"
#include "Color.h"

class Screen;
struct BoundaryEdge;

namespace tetronimosSpace
{
	enum TetronimosDirection
	{
		LEFT = 1 << 0,
		RIGHT = 1 << 1
	};
}

class Tetronimos : public Excluder
{
public:	
	Tetronimos();

	//from paddle.h
	static const uint32_t BLOCK_WIDTH = 20;
	static const uint32_t BLOCK_HEIGHT = 20;
	void Init(const AARectangle& rect, const AARectangle& block);
	inline void SetMovementDirection(tetronimosSpace::TetronimosDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(tetronimosSpace::TetronimosDirection dir) { mDirection &= ~dir; }
	inline void StopMovement() { mDirection = 0; }
	inline bool IsMovingLeft() const { return mDirection == tetronimosSpace::TetronimosDirection::LEFT; }
	inline bool IsMovingRight() const { return mDirection == tetronimosSpace::TetronimosDirection::RIGHT; }

	//from ball.h
	void Update(uint32_t dt);
	void Draw(Screen& screen);
	inline void Stop() { mVelocity = Vect2D::Zero; }
	inline void SetVelocity(const Vect2D& vel) { mVelocity = vel; }
	inline Vect2D GetVelocity() const { return mVelocity; }
	

private:
	//from paddle.h and ball.h
	AARectangle mTetrisBoundary; // game bounderies
	uint32_t mDirection; // direction we are moving
	const float LeftRightVELOCITY = 200.0f; // 200 pixels per seconds
	Vect2D mVelocity;
	Color mOutlineColor;
	Color mFillColor;
};



#endif // !GAMES_TETRIS_TETRONIMOS_H_


