
#include "SceneManager.h"
#include "../CatGameLib/CatGameLib.h"
#include "Title.h"

using namespace CatGameLib;
using namespace MagicalBook;

Title::Title() : test( nullptr),
				 fox( nullptr),
				 fox2( nullptr)
{
	test = LibSprite::create( "background/books.png");
}

Title::~Title()
{
}

LibSound* sound;

void Title::init( void)
{
	sound = LibSound::create( "test.wav");
	sound -> setVolume( 1.0f);
//	sound -> play();

	test -> setPosition( 1280 / 2, 720 / 2);
}

void Title::update( void)
{
	test -> draw();
}