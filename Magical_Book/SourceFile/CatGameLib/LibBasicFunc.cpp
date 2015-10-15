
#include "LibBasicFunc.h"

using namespace CatGameLib;

int LibBasicFunc::wrap( int x, int low, int high)
{
	assert( low < high);
	const int n = ( x - low) % ( high - low);
	return ( n >= 0) ? ( n + low) : ( n + high);
}

float LibBasicFunc::wrap( float x, float low, float high)
{
	assert( low < high);
	const float n = std::fmod( ( x - low), ( high - low));
	return ( n >= 0) ? ( n + low) : ( n + high);
}
