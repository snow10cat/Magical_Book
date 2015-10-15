
#ifndef __CAT_GAME_LIBRARY_VECTOR2_H__
#define __CAT_GAME_LIBRARY_VECTOR2_H__

namespace CatGameLib
{

class LibVector2
{
public:
	LibVector2() : x( 0.0f), 
				   y( 0.0f)
	{
	}

	LibVector2( float x) : x( x), 
						   y( x)
	{
	}

	LibVector2( float x, float y) : x( x),
								    y( y)
	{
	}


	float x;
	float y;

private:

};

}

#endif // __CAT_GAME_LIBRARY_VECTOR2_H__