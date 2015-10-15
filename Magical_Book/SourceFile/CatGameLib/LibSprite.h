
#ifndef __CAT_GAME_LIBRARY_SPRITE_H__
#define __CAT_GAME_LIBRARY_SPRITE_H__

#include "LibCircle.h"
#include "LibVector2.h"

namespace CatGameLib
{

class LibSprite
{
public:
	enum
	{
		LoadSpriteMax = 1024,
	};

	static unsigned int * getTextureIDs( void) { return textureIDs; }

	static LibSprite* create( const char* fileName);

	void setAlpha( float alpha);

	void setPosition( float x, float y);
	void setPosition( const LibVector2& pos);

	void setRotation( int angle);
	void setRotation( float angle);

	void setScale( float scale);
	void setScale( float x, float y);
	void setScale( const LibVector2& scale);


	void draw( void);
	~LibSprite();

private:
	static int loadCount;
	static unsigned int textureIDs[LoadSpriteMax];

	int textureNumber;
	GLuint sizeX;
	GLuint sizeY;
	float alpha;

	LibCircle angle;
	LibVector2 position;
	LibVector2 scale;
	LibVector2 anchor;

	LibSprite();

	void loadTexture( const char* fileName);
};

}


#endif // __CAT_GAME_LIBRARY_SPRITE_H__
