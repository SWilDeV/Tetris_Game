#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include "Shapes.h"

class Circle: public Shape
{
	public:
		Circle();
		Circle(const Vect2D& center, float radius);

		inline virtual Vect2D GetCenterPoint() const override { return mPoints[0]; }
	
		inline void SetRadius(float radius) { mRadius = radius; }
		inline float GetRadius() const { return mRadius; }
		
		inline virtual void MoveTo(const Vect2D& position) override { mPoints[0] = position; }

		bool Intersects(const Circle& otherCircle) const;
		bool ContainsPoint(const Vect2D& point) const;

	private:
		float mRadius;
};
#endif // !SHAPES_CIRCLE_H_
