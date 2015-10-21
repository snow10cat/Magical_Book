
#include "CatGameLib.h"
#include "Game.h"

using namespace CatGameLib;
using namespace MagicalBook;

Game::Game() : books( nullptr),
				 fox( nullptr),
				 fox2( nullptr)
{
	//books = CatGameLib::LibSprite::create( "background/gane_bg1.png");
}

Game::~Game()
{
}

void Game::init( void)
{
	/*test -> setPosition( 1280 / 2, 720 / 2);

	test -> setScale( 1.0f);*/
}

void Game::update( void)
{
	//test -> draw();
}