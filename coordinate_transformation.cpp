#include "coordinate_transformation.h"

bool convert_coordinates(float inX, float inY, float  maxX, float  maxY, float* outX, float* outY) {
	*outX = inX + (maxX / 2.0f);
	*outY = (3.0*maxY / 4.0f) - inY;
	return true;
}
