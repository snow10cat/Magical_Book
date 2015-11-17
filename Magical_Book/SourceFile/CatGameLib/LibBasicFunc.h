
#ifndef __CAT_GAME_LIBRARY_BASIC_FUNC_H__
#define __CAT_GAME_LIBRARY_BASIC_FUNC_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

#define PI 3.141592f
#define DEGREE_TO_RADIAN(deg) (deg * PI / 180.0f)

namespace CatGameLib
{

class LibBasicFunc
{
public:
	template<class T>
	static T clamp(T x, T low, T high)
	{
		assert(low <= high);
		return std::min(std::max(x, low), high);
	}

	template<class T>
	static void clamp(T* x, T low, T high)
	{
		assert(low <= high && x != nullptr);
		*x = std::min(std::max(*x, low), high);
	}

	static int wrap(int x, int low, int high);
	static float wrap(float x, float low, float high);
};

}

#endif // __CAT_GAME_LIBRARY_BASIC_FUNC_H__
