
#include "SceneManager.h"
#include "../CatGameLib/CatGameLib.h"
#include "Title.h"

using namespace CatGameLib;
using namespace MagicalBook;

Title::Title() : floar(nullptr),
				 title_book(nullptr),
				 title_logo(nullptr)
{
	floar = LibSprite::create("background/floar.png");
	title_book = LibSprites::create("background/title.png", 1000, 500);
	title_logo = LibSprite::create("logo/title_logo.png");
	player = LibSprites::create( "player/player_walk.png", 34, 68);
}

Title::~Title()
{
}

LibSound* sound;

//‰Šú‰»
void Title::init(void)
{
	sound = LibSound::create("bgm/title.wav");
	sound->setVolume(1.0f);
	sound->play();

	floar->setPosition(1280 / 2, 720 / 2);
	floar->setScale(1.0f);

	title_book -> setPosition(1280 / 2 - 250, 720 / 2);
	title_book -> setAnimationSpeed(50);

	title_logo->setPosition(1280 / 2, 720 / 2 + 250);
	title_logo->setScale(0.5f);

	player -> setPosition( 1020, 120);
	player -> setAnimationSpeed( 10);
}

//XV
void Title::update(void)
{
	floar->draw();
	title_book -> animation();
	title_logo -> draw();

	player -> animation();
	

	if( LibInput::getInstance() -> getKeyboardState( LibInput::KeyBoardNumber::Key_Enter))
	{
		sound -> allStop();
		SceneManager::getInstance()->createScene(SceneManager::SceneNumber::Game);
	}
}