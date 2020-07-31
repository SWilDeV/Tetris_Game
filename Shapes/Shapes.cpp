#include "Shapes.h"

void Shape::MoveBy(const Vect2D& deltaOffset)
{
	for (Vect2D& point : mPoints)
	{
		point = point + deltaOffset;
	}
}

