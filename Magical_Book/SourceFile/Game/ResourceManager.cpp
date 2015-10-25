
#include "CatGameLib.h"
#include "ResourceManager.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


ResourceManager::ResourceManager()
{	
}


ResourceManager::~ResourceManager()
{
}


void ResourceManager::loadResource( void)
{
	//����
	soundArray["selectbgm"] = LibSound::create( "bgm/select.wav");
	soundArray["bgm1"] = LibSound::create( "bgm/stage1.wav");
	soundArray["bgm2"] = LibSound::create( "bgm/stage2.wav");
	soundArray["bgm3"] = LibSound::create( "bgm/stage3.wav");
	soundArray["menuSelect"] = LibSound::create("se/select.wav");
	soundArray["menuOk"] = LibSound::create( "se/page.wav");
	soundArray["pageNext"] = LibSound::create( "se/page.wav");

	//�摜
	spriteArray["fadeout"] = LibSprite::create("background/fadeout.png");
	spriteArray["floar"] = LibSprite::create("background/floar.png");
	spriteArray["frame"] = LibSprite::create("background/frame.png");
	
	spriteArray["back"] = LibSprite::create("logo/back.png");

	spritesArray["books"] = CatGameLib::LibSprites::create("background/books.png", 1000, 500);
	spritesArray["openBook"] = CatGameLib::LibSprites::create("background/open.png", 1000, 500);
	spritesArray["closeBook"] = CatGameLib::LibSprites::create("background/close.png", 1000, 500);
	spritesArray["mapchip"] = CatGameLib::LibSprites::create("mapchip/mapchip.png", 34, 34);

	for(int i = 1; i <= BG_Count; i++)
	{
		string fileName = "game_bg" + to_string( i);
		string filePass =  "background/" + fileName + ".png";

		spriteArray[fileName] = LibSprite::create(filePass.c_str());
	}
}


LibSound* ResourceManager::getSound(const string& fileName)
{
	return soundArray[fileName];
}


LibSprite* ResourceManager::getSprite(const string& fileName)
{
	return spriteArray[fileName];
}


LibSprites* ResourceManager::getSprites(const string& fileName)
{
	return spritesArray[fileName];
}