#ifndef GAMES_BREAKOUT_BALL_H_
#define GAMES_BREAKOUT_BALL_H_

#include "AARectangle.h"
#include <stdint.h>
#include "BoundaryEdge.h"


class Screen;
struct BoundaryEdge;

class Ball
{
public:
	Ball();
	Ball(const Vect2D& pos, float radius);

	void Update(uint32_t dt);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vect2D& pointOnEdge, bool limitToEdge);
	void MoveTo(const Vect2D& point);
	void Bounce(const BoundaryEdge& edge);


	inline void Stop() { mVelocity = Vect2D::Zero; }
	inline const AARectangle GetBoundingRect() const { return mBBox; }
	inline void SetVelocity(const Vect2D& vel) { mVelocity = vel; }
	inline Vect2D GetVelocity() const { return mVelocity; }
	inline float GetRadius() const { return mBBox.GetWidth()/ 2.0f; }
	inline Vect2D GetPosition() const { return mBBox.GetCenterPoint(); }

private:
	AARectangle mBBox;
	Vect2D mVelocity;
	static const float RADIUS;
};

#endif // !GAMES_BREAKOUT_BALL_H_

