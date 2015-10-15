
#include "Game.h"

using namespace MagicalBook;

Game::Game() : test( nullptr),
				 fox( nullptr),
				 fox2( nullptr)
{
	test = CatGameLib::LibSprite::create( "rgb.png");
}

Game::~Game()
{
}

void Game::init( void)
{
	test -> setPosition( 1280 / 2, 720 / 2);

	test -> setScale( 5.0f);
}

void Game::update( void)
{
	test -> draw();
}