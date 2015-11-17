
#include "CatGameLib.h"
#include "Game.h"
#include "../Game/Player.h"

using namespace CatGameLib;
using namespace MagicalBook;

Game::Game()
{
}

Game::~Game()
{
	delete stage;
	stage = nullptr;
}

void Game::init(void)
{
	stage = new Stage();
	characters.push_back(new Player());

	for(int i = 0; i < characters.size(); i++)
	{
		characters[i] -> init();
	}
}

void Game::update(void)
{
	stage -> update();
	for(int i = 0; i < characters.size(); i++)
	{
		characters[i] -> update(stage);
	}

	stage -> draw();
	for(int i = 0; i < characters.size(); i++)
	{
		characters[i] -> draw();
	}
}