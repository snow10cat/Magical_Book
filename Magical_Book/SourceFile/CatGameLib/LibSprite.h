
#ifndef __CAT_GAME_LIBRARY_SPRITE_H__
#define __CAT_GAME_LIBRARY_SPRITE_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace CatGameLib
{

class LibSprite
{
public:
	static LibSprite* create( const char* fileName);
	static void allRelease( void);

	void setAlpha( float alpha);

	void setAnchorPoint( float pos);
	void setAnchorPoint( float x, float y);
	void setAnchorPoint( const CatGameLib::LibVector2& pos);

	void setPosition( float x, float y);
	void setPosition( const LibVector2& pos);

	void setRotation( int angle);
	void setRotation( float angle);

	void setScale( float scale);
	void setScale( float x, float y);
	void setScale( const LibVector2& scale);

	float getAlpha( void);
		 
	float getAnchorPointX( void);
	float getAnchorPointY( void);
	LibVector2 getAnchorPoint( void);
		 
	float getPositionX( void);
	float getPositionY( void);
	LibVector2 getPosition( void);
		 
	int getRotationDegree( void);
	float getRotationRadian( void);
		 
	float getScaleX( void);
	float getScaleY( void);
	LibVector2 getScale( void);

	void draw( void);
	~LibSprite();

private:
	enum
	{
		LoadSpriteMax = 1024,
	};

	static int loadCount;
	static unsigned int textureIDs[LoadSpriteMax];

	unsigned int textureID;

	bool isRender;
	GLuint sizeX;
	GLuint sizeY;
	float alpha;

	LibCircle angle;
	LibVector2 anchor;
	LibVector2 position;
	LibVector2 scale;

	LibSprite();

	void loadTexture( const char* fileName);
};

}


#endif // __CAT_GAME_LIBRARY_SPRITE_H__
