
#include "../Game/SpriteManager.h"
#include "SceneManager.h"
#include "CatGameLib.h"
#include "Title.h"


#define BOOK_ANM_MAX 7


using namespace CatGameLib;
using namespace MagicalBook;

SpriteManager* instance = SpriteManager::getInstance();

Title::Title() : title_book(nullptr),
				 title_logo(nullptr),
				 title_start(nullptr),
				 title_end(nullptr)
{
	title_book  = LibSprites::create("background/title.png", 1000, 500);
	title_logo  = LibSprite::create("logo/title_logo.png");
	title_start = LibSprite::create("logo/title_start.png");
	title_end	= LibSprite::create("logo/title_end.png");
}


Title::~Title()
{
}


//初期化
void Title::init(void)
{
	input = LibInput::getInstance();

	title_bgm = LibSound::create("bgm/title.wav");
	title_bgm -> setVolume(1.0f);
	title_bgm -> setLoop(true);

	select_se = LibSound::create("se/select.wav");
	select_se -> setVolume(1.0f);

	game_in = LibSound::create("se/in.wav");
	game_in -> setVolume(1.0f);

	instance ->getSprite("fadeout") -> setPosition(sWHeaf, sHHeaf);
	instance ->getSprite("fadeout") -> setScale(1.0f);
	instance ->getSprite("fadeout") -> setAlpha(0.0f);

	instance ->getSprite("floar") -> setPosition(sWHeaf, sHHeaf);
	instance ->getSprite("floar") -> setScale(1.0f);

	title_book -> setPosition(sWHeaf - 250, sHHeaf);
	title_book -> setScale(1.0f);

	title_logo -> setPosition(sWHeaf + 25, sHHeaf + 150);
	title_logo -> setScale(0.5f);

	title_start -> setPosition(sWHeaf + 25, sHHeaf - 50);
	title_start -> setScale(1.0f);

	title_end -> setPosition(sWHeaf + 25, sHHeaf - 150);
	title_end -> setScale(0.7f);

	counter = 0;
	flag = 0;
	anime_number = 0;
	size = 1;
	title_work = Select;
}


//更新
void Title::update(void)
{
	instance ->getSprite("floar") -> draw();

	if(title_bgm -> getState() != LibSound::Play)
	{
		title_bgm -> play();
	}

	switch (title_work)
	{
	case Select:
		title_book -> draw(0);
		title_logo -> draw();
		title_start -> draw();
		title_end -> draw();

		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter++;
			select_se -> play();
		}

		if (counter % 2 == 0)
		{
			//ゲーム本編
			title_start -> setScale(1.0f);
			title_end -> setScale(0.7f);
			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				counter = 0;
				title_work = Animation;
			}
		}
		else if (counter % 2 == 1)
		{
			//ゲーム終了
			title_start -> setScale(0.7f);
			title_end -> setScale(1.0f);
			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				title_work = Animation;
			}
		}
		break;
	case Animation:
		title_book -> draw(anime_number);
		title_book -> setPositionX(title_book -> getPositionX() + 5);
		
		if(anime_number < BOOK_ANM_MAX)
		{
			counter++;
			if(counter % 7 == 0)
			{
				anime_number++;
			}
		}

		if (title_book -> getPositionX() >= sWHeaf)
		{
			title_book -> setPositionX(sWHeaf);
			if(anime_number == BOOK_ANM_MAX)
			{
				title_work = Fadeout;
			}
		}
		break;
	case Fadeout:
		title_book -> draw(BOOK_ANM_MAX);
		title_book -> setScale(size);

		instance ->getSprite("fadeout") -> draw();
		instance ->getSprite("fadeout") -> setAlpha(instance ->getSprite("fadeout") -> getAlpha() + 5);
		
		if(flag == 0)
		{
			game_in -> play();
			flag = 1;
		}
		else if(flag == 1 && game_in -> getState() != LibSound::Play)
		{
			title_work = Next;
		}

		if(size >= 1.8f)
		{
			size = 1.8f;
		}
		else
		{
			size += 0.01f;
		}

		if(instance ->getSprite("fadeout") -> getAlpha() == 255)
		{
			instance ->getSprite("fadeout") -> setAlpha(255);
		}
		break;
	case Next:
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Stageselect);
		break;

	}
}