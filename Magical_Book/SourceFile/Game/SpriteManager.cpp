


#include "CatGameLib.h"
#include "SpriteManager.h"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

static SpriteManager* instance = SpriteManager::getInstance();

SpriteManager::SpriteManager()
{
	
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::loadSprite( void)
{
	spriteArray["fadeout"] = LibSprite::create("background/fadeout.png");
	spriteArray["floar"] = LibSprite::create("background/floar.png");

	spritesArray["books"] = CatGameLib::LibSprites::create("background/books.png", 1000, 500);
	spritesArray["mapchip"] = CatGameLib::LibSprites::create("mapchip/mapchip.png", 1000, 500);

	for(int i = 1; i <= BG_Count; i++)
	{
		string fileName = "game_bg" + to_string( i);
		string filePass =  "background/" + fileName + ".png";

		spriteArray[fileName] = LibSprite::create(filePass.c_str());
	}
}

LibSprite* SpriteManager::getSprite(const string& fileName)
{
	return spriteArray[fileName];
}

LibSprites* SpriteManager::getSprites(const string& fileName)
{
	return spritesArray[fileName];
}
