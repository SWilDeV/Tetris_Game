#ifndef SHAPES_AARECTANGLE_H_
#define SHAPES_AARECTANGLE_H_
#include "Shapes.h"

using namespace std;

class AARectangle : public Shape
{
public:
	AARectangle();
	AARectangle(const Vect2D& topLeft, unsigned int width, unsigned int heigth);
	AARectangle(const Vect2D& topLeft, const Vect2D& bottomRight);

	inline void SetTopLeftPoint(const Vect2D& topLeft) { mPoints[0] = topLeft; }
	inline void SetBottomRightPoint(const Vect2D& bottomRight) { mPoints[1] = bottomRight; }
	inline Vect2D GetTopLeftPoint() const { return mPoints[0]; }
	inline Vect2D GetBottomRightPoint() const{ return mPoints[1]; }

	float GetWidth() const;
	float GetHeigth() const;

	virtual void MoveTo(const Vect2D& position) override;

	virtual Vect2D GetCenterPoint() const override;

	bool Intersects(const AARectangle& otherRect) const;
	bool ContainsPoint(const Vect2D& point) const;

	static AARectangle Inset(const AARectangle& rect, Vect2D& insets);

	virtual vector<Vect2D> GetPoints() const override;

};

#endif // SHAPES_AARECTANGLE_H_
