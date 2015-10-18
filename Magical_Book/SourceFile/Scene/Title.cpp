
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
	//title_book = LibSprite::create("background/title.png");
	title_logo = LibSprite::create("logo/title_logo.png");
	player = LibSprites::create( "player/player_walk.png", 34, 68);
}

Title::~Title()
{
}

LibSound* sound;
void Title::init(void)
{
	sound = LibSound::create("bgm/title.wav");
	sound->setVolume(1.0f);
	sound->play();

	floar->setPosition(1280 / 2, 720 / 2);
	floar->setScale(1.0f);
	//fox -> setAlpha( 128.0);

	title_logo->setPosition(1280 / 2, 720 / 2);
	title_logo->setScale(1.0f);

	player -> setPosition( 1020, 120);
	player -> setAnimationSpeed( 10);
}

void Title::update(void)
{
	floar->draw();
	//title_book -> draw();
	title_logo -> draw();

	player -> animation();

	if( LibInput::getInstance() -> getKeyboardState( LibInput::KeyBoardNumber::Key_Enter))
	{
		sound -> stop();
		SceneManager::getInstance()->createScene(SceneManager::SceneNumber::Game);
	}
}