
#ifndef __CAT_GAME_LIBRARY_SPRITE_H__
#define __CAT_GAME_LIBRARY_SPRITE_H__

#include "LibCircle.h"
#include "LibVector2.h"

namespace CatGameLib
{

class LibSprite
{
public:
	static LibSprite* create( const char* fileName);
	static void allRelease( void);

	void setDrawFlag( bool flag);

	void setAlpha( float alpha);

	void setAnchorPoint( float pos);
	void setAnchorPoint( float x, float y);
	void setAnchorPoint( const CatGameLib::LibVector2& pos);
	void setAnchorPointX( float pos);
	void setAnchorPointY( float pos);

	void setPosition( float x, float y);
	void setPosition( const LibVector2& pos);
	void setPositionX( float pos);
	void setPositionY( float pos);

	void setRotation( int angle);
	void setRotation( float angle);

	void setScale( float scale);
	void setScale( float x, float y);
	void setScale( const LibVector2& scale);
	void setScaleX( float scale);
	void setScaleY( float scale);

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

	float getTextureSizeX( void);
	float getTextureSizeY( void);
	LibVector2 getTextureSize( void);

	void draw( void);
	~LibSprite();

protected:
	enum
	{
		LoadSpriteMax = 1024,
	};

	static int loadCount;
	static unsigned int textureIDs[LoadSpriteMax];

	unsigned int textureID;

	bool isDraw;
	unsigned int sizeX;
	unsigned int sizeY;
	float alpha;

	LibCircle angle;
	LibVector2 anchor;
	LibVector2 position;
	LibVector2 scale;

	LibSprite();

	void loadTexture( const char* fileName);
	void drawTexture( int number);
};

}

#endif // __CAT_GAME_LIBRARY_SPRITE_H__
