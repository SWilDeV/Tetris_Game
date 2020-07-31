#ifndef SHAPES_LINE2D_H
#define SHAPES_LINE2D_H
#include "Vec2D.h"
#include "Utils.h"

class Line2D
{
public:

	Line2D();
	Line2D(float x0, float y0, float x1, float y1);
	Line2D(const Vect2D& p0, const Vect2D& p1);

	inline const Vect2D& GetP0() const { return mP0; }
	inline const Vect2D GetP1() const { return mP1; }

	inline void SetP0(const Vect2D& p0) { mP0 = p0; }
	inline void SetP1(const Vect2D& p1) { mP1 = p1; }

	bool operator==(const Line2D& line);
	float MinDistanceFrom(const Vect2D& p, bool limitToSegment) const;
	Vect2D ClosestPoint(const Vect2D& p, bool limitToSegment) const;

	Vect2D MidPoint() const;
	float Slope() const;
	float Length() const;

private:
	Vect2D mP0;
	Vect2D mP1;

};

#endif // !SHAPES_LINE2D_H

