
#ifndef __CAT_GAME_LIBRARY_SPRITES_H__
#define __CAT_GAME_LIBRARY_SPRITES_H__

#include "CatGameLib.h"
#include "LibSprite.h"

namespace CatGameLib
{

class LibSprites : public LibSprite
{
public:
	static LibSprites* create(const char* fileName, int width, int height);
	static void allRelease(void);

	void setAnimationSpeed(int speed);
	int getSpriteCount(void);

	void draw(int number);
	void animation(void);

	~LibSprites();

private:
	static int allObjectLoadCount;
	static unsigned int allObjectTextureIDs[LoadSpriteMax * 8];

	std::vector<unsigned int> textureIDArray;
	int textureNumber;
	int spriteCount;
	unsigned char* pixelBuffer;

	int animationSpeed;
	int animationCount;
	int animationNumber;

	LibSprites();

	void createTexture(png::image<png::rgba_pixel>& image, int number, int posX, int posY);
};

}


#endif // __CAT_GAME_LIBRARY_SPRITES_H__
