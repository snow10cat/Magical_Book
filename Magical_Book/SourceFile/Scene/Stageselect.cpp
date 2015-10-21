
#include "CatGameLib.h"
#include "Stageselect.h"


using namespace CatGameLib;
using namespace MagicalBook;


Stageselect::Stageselect() : books( nullptr)
{
	books = CatGameLib::LibSprites::create("background/books.png", 1000, 500);
	game_bg1 =CatGameLib::LibSprite::create("background/game_bg1.png");
	game_bg2 =CatGameLib::LibSprite::create("background/game_bg2.png");
}


Stageselect::~Stageselect()
{
}


void Stageselect::init( void)
{
	books -> setPosition(sWHeaf + 300, sHHeaf);
	books -> setScale(1.5f);
}


void Stageselect::update( void)
{
	books -> draw(0);
}