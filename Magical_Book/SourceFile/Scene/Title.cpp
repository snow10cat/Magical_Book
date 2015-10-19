
#include "SceneManager.h"
#include "CatGameLib.h"
#include "Title.h"

using namespace CatGameLib;
using namespace MagicalBook;

Title::Title() : floar(nullptr),
				 title_book(nullptr),
				 title_logo(nullptr)
{
	floar		= LibSprite::create("background/floar.png");
	title_book  = LibSprites::create("background/title.png", 1000, 500);
	title_logo  = LibSprite::create("logo/title_logo.png");
	title_start = LibSprite::create("logo/title_start.png");
	title_end	= LibSprite::create("logo/title_end.png");
	player		= LibSprites::create( "player/player_walk.png", 34, 68);
}

Title::~Title()
{
}

LibSound* sound;

//‰Šú‰»
void Title::init(void)
{
	sound = LibSound::create("bgm/title.wav");
	sound -> setVolume(1.0f);
	sound -> play();

	floar -> setPosition(1280 / 2, 720 / 2);
	floar -> setScale(1.0f);

	title_book -> setPosition(1280 / 2 - 250, 720 / 2);
	title_book->setScale(1.0f);
	title_book -> setAnimationSpeed(100);

	title_logo -> setPosition(1280 / 2 + 25, 720 / 2 + 150);
	title_logo -> setScale(0.5f);

	title_start -> setPosition(1280 / 2 + 25, 720 / 2 - 50);
	title_start -> setScale(1.0f);

	title_end -> setPosition(1280 / 2 + 25, 720 / 2 - 150);
	title_end -> setScale(1.0f);

	player -> setPosition(1020, 120);
	player -> setAnimationSpeed(50);

	title_work = Init;
}

//XV
void Title::update(void)
{
	floar -> draw();

	player -> animation();
	
	switch (title_work)
	{
	case Init:
		counter = 0;
		title_work = Choose;
		break;
	case Choose:
		title_book -> draw(0);
		title_logo -> draw();
		title_start -> draw();
		title_end -> draw();

		if (LibInput::getInstance()->getKeyboardState(LibInput::KeyBoardNumber::Key_Up) || LibInput::getInstance()->getKeyboardState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter++;
			//SEÄ¶;
		}
		if (counter % 3 == 0)
		{
			//ƒQ[ƒ€–{•Ò
			title_start -> setScale(1.0f);
			title_end -> setScale(0.8f);
			if (LibInput::getInstance()->getKeyboardState(LibInput::KeyBoardNumber::Key_Z))
			{
				title_work = Animation;
			}
		}
		if (counter % 3 == 1)
		{
			//ƒQ[ƒ€§ì
			title_start -> setScale(0.8f);
			title_end -> setScale(1.0f);
			if (LibInput::getInstance()->getKeyboardState(LibInput::KeyBoardNumber::Key_Z))
			{
				title_work = Animation;
			}
		}
		if (counter % 3 == 2)
		{
			//ƒQ[ƒ€I—¹
		}
		break;
	case Animation:
		title_book->animation();
		//if ()
		
		break;
	case Fadeout:
		if (LibInput::getInstance()->getKeyboardState(LibInput::KeyBoardNumber::Key_X))
		{
			title_work = Next;
		}
		
		break;
	case Next:
		sound -> allStop();
		if(LibInput::getInstance() -> getKeyboardState(LibInput::KeyBoardNumber::Key_Enter))
		{
			if (counter % 3 == 0)
			{
				SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
			}
			if (counter % 3 == 1)
			{
				//ƒQ[ƒ€§ì
				SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
			}
			title_work = Init;
		}
		break;

	}
}