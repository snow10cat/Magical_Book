
#include <iostream>
#include <cmath>

#include "CatGameLib.h"

using namespace CatGameLib;

int LibBaseFunc::wrap( int x, int low, int high)
{
	assert( low < high);
	const int n = ( x - low) % ( high - low);
	return ( n >= 0) ? ( n + low) : ( n + high);
}

float LibBaseFunc::wrap( float x, float low, float high)
{
	assert( low < high);
	const float n = std::fmod( ( x - low), ( high - low));
	return ( n >= 0) ? ( n + low) : ( n + high);
}
