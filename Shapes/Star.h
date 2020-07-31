#ifndef SHAPES_STAR_H_
#define SHAPES_STAR_H_
#include "Vec2D.h"
#include <random>
#include <time.h>
#include "Utils.h"
#include <iostream>

#include <vector>
using namespace std;
class Star
{
public:
	
	Star();

	double CreateRandomNumber();
	

	inline vector <Vect2D> GetPoints() const { return mPoints; }
	inline Vect2D GetCenterPoint() { return mPoints[0]; }

	/*inline void SetP0(const Vect2D& p0) { mPoints[0] = p0; }
	inline void SetP1(const Vect2D& p1) { mPoints[1] = p1; }
	inline void SetP2(const Vect2D& p2) { mPoints[2] = p2; }
	inline void SetP3(const Vect2D& p3) { mPoints[3] = p3; }
	inline void SetP4(const Vect2D& p4) { mPoints[4] = p4; }*/

	inline Vect2D GetP0() const { return mPoints[0]; }
	inline Vect2D GetP1() const { return mPoints[1]; }
	inline Vect2D GetP2() const { return mPoints[2]; }
	inline Vect2D GetP3() const { return mPoints[3]; }
	inline Vect2D GetP4() const { return mPoints[4]; }
	inline Vect2D GetP5() const { return mPoints[5]; }
	inline Vect2D GetP6() const { return mPoints[6]; }

	void RotatePoint(float angle, const Vect2D& position);
	

private:
	vector<Vect2D> mPoints;
	float rotSpeed;

	float angle = TWO_PI / 5.0f;
	
};


#endif //SHAPES_STAR_H_
