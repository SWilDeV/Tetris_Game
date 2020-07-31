#include "Star.h"
#include "Utils.h"

Star::Star()
{
	rotSpeed = CreateRandomNumber();

	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_real_distribution<> dis(50, 550);//random number between 50 and 550
	std::uniform_int_distribution<> dis2(50, 200);//random number between 50 and 200

	float starX = dis(e1);
	float starY = dis(e1);
	float starRad = dis2(e1);
	Vect2D starRadVec = { starRad, starRad };
	Vect2D starCenterPoint = { starX, starY };

	
	Vect2D p1 = { starCenterPoint.GetX() + starRad, starCenterPoint.GetY() };
	Vect2D p2 = { p1.RotationResult(angle,starCenterPoint) };
	Vect2D p3 = { p1.RotationResult(2*angle,starCenterPoint) };
	Vect2D p4 = { p1.RotationResult(3*angle,starCenterPoint) };
	Vect2D p5 = { p1.RotationResult(4*angle,starCenterPoint) };

	mPoints.push_back(starCenterPoint);
	mPoints.push_back(starRadVec);
	mPoints.push_back(p1);
	mPoints.push_back(p2);
	mPoints.push_back(p3);
	mPoints.push_back(p4);
	mPoints.push_back(p5);

}

void Star::RotatePoint(float angle, const Vect2D& position)
{

	mPoints[2] = mPoints[2].RotationResult(angle * rotSpeed, position);
	mPoints[3] = mPoints[3].RotationResult(angle * rotSpeed, position);
	mPoints[4] = mPoints[4].RotationResult(angle * rotSpeed, position);
	mPoints[5] = mPoints[5].RotationResult(angle * rotSpeed, position);
	mPoints[6] = mPoints[6].RotationResult(angle * rotSpeed, position);
}

double Star::CreateRandomNumber()
{
	std::random_device rd;
	std:default_random_engine e1(rd());
	std::uniform_real_distribution<> dis(-2, 2);//random number between 0.1 and 2

	double b = dis(e1);
	return b;
}
