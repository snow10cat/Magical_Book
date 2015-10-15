
#include "Title.h"

using namespace MagicalBook;

Title::Title() : test( nullptr),
				 fox( nullptr),
				 fox2( nullptr)
{
	test = CatGameLib::LibSprite::create( "test2.png");
	fox = CatGameLib::LibSprite::create( "Fox.png");
	fox2 = CatGameLib::LibSprite::create( "Fox3.png");
}

Title::~Title()
{
}

void Title::init( void)
{
	

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
//	fox2 -> draw();
	fox -> draw();
//	test -> draw();
}