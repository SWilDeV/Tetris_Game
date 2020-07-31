#ifndef SHAPES_TRIANGLE_H_
#define SHAPES_TRIANGLE_H_
#include "Shapes.h"

class Triangle : public Shape
{
public:
	Triangle();
	Triangle(const Vect2D& p0, const Vect2D& p1, const Vect2D& p2);

	inline void SetP0(const Vect2D& p0) { mPoints[0] = p0; }
	inline void SetP1(const Vect2D& p1) { mPoints[1] = p1; }
	inline void SetP2(const Vect2D& p2) { mPoints[2] = p2; }

	inline Vect2D GetP0() const { return mPoints[0]; }
	inline Vect2D GetP1() const { return mPoints[1]; }
	inline Vect2D GetP2() const { return mPoints[2]; }

	virtual Vect2D GetCenterPoint() const override;
	float Area() const;
	bool ContainsPoint(const Vect2D& p) const;

	virtual void MoveTo(const Vect2D& newPosition) override;
	

private:
	float Area(const Vect2D& p0, const Vect2D& p1, const Vect2D& p2) const;
};

#endif //SHAPES_TRIANGLE_H_
