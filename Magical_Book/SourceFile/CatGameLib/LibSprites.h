
#ifndef __CAT_GAME_LIBRARY_SPRITES_H__
#define __CAT_GAME_LIBRARY_SPRITES_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace CatGameLib
{

class LibSprites
{
public:
	static LibSprites* create( const char* fileName, int width, int height);
	static void allRelease( void);

	void setAlpha( float alpha);

	void setAnimationSpeed( int speed);

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
		 
	int getAnimationSpeed( void);
		 
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

	int getSpriteCount( void);

	void draw( int number);
	void animation( void);

	~LibSprites();

private:
	enum
	{
		LoadSpriteMax = 1024,
	};

	static int loadCount;
	static unsigned int allObjectTextureIDs[LoadSpriteMax];

	std::vector<unsigned int> textureIDs;
	int textureNumber;
	int spriteCount;
	unsigned int* pixelBuffer;

	int animationSpeed;
	int animationCount;
	int animationNumber;

	bool isRender;
	GLuint sizeX;
	GLuint sizeY;
	float alpha;

	LibCircle angle;
	LibVector2 anchor;
	LibVector2 position;
	LibVector2 scale;

	LibSprites();

	void createTexture( png::image<png::rgba_pixel>& image, int number, int posX, int posY);
};

}


#endif // __CAT_GAME_LIBRARY_SPRITES_H__
