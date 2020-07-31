#ifndef SHAPES_SHAPES_H_
#define SHAPES_SHAPES_H_
#include "Vec2D.h"
#include <vector>

using namespace std;


class Shape
{
public:
	virtual Vect2D GetCenterPoint() const = 0;
	virtual ~Shape(){}

	inline virtual vector <Vect2D> GetPoints() const { return mPoints; }
	void MoveBy(const Vect2D& deltaOffset);

	virtual void MoveTo(const Vect2D& newPosition) = 0;
	

protected:
	vector<Vect2D> mPoints;
};


#endif // !SHAPES_SHAPES_H_
