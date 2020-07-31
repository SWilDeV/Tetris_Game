#ifndef  UTILIS_UTILS_H_
#define  UTILIS_UTILS_H_
#include <iostream>

static const float EPSILON = 0.0001f;

const float PI = 3.14159;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MilliSecondsToSeconds(unsigned int milliseconds);

#endif // ! UTILIS_UTILS_H_

