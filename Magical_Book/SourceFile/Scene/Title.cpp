
#include "SceneManager.h"
#include "../CatGameLib/CatGameLib.h"
#include "Title.h"

using namespace CatGameLib;
using namespace MagicalBook;

Title::Title() : test( nullptr),
				 fox( nullptr),
				 fox2( nullptr)
{
	test = LibSprite::create( "test2.png");
	fox = LibSprite::create( "Fox.png");
	fox2 = LibSprite::create( "Fox3.png");
}

Title::~Title()
{
}
LibSound* sound;
void Title::init( void)
{
	sound = LibSound::create( "test.wav");
	sound -> setVolume( 1.0f);
	sound -> play();

	test -> setPosition( 1280 / 2, 720 / 2);
	
	fox -> setRotation( 45);
	fox -> setPosition( 1280 / 2, 720 / 2);
	fox -> setScale( 1.0f);
//	fox -> setAlpha( 128.0);

	fox2 -> setPosition( 1280 / 2, 720 / 2);
	fox2 -> setScale( 1.0f);
}

void Title::update( void)
{
	static int speedX = 0;
	fox -> setPosition( speedX, 720 / 2);
	speedX++;

	if( speedX > 1000)
	{
		SceneManager::getInstance() -> createScene( SceneManager::Game);
		LibSprite::allRelease();
		return;
	}


	fox2 -> draw();
	fox -> draw();
	test -> draw();
}