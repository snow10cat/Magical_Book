
#include "SceneManager.h"
#include "CatGameLib.h"
#include "Title.h"


#define BOOK_ANM_MAX 7


using namespace CatGameLib;
using namespace MagicalBook;


Title::Title() : floar(nullptr),
				 title_book(nullptr),
				 title_logo(nullptr)
{
	fadeout		= LibSprite::create("background/bg.png");
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


//初期化
void Title::init(void)
{
	input = LibInput::getInstance();

	sound = LibSound::create("bgm/title.wav");
	sound -> setVolume(1.0f);
	sound -> play();

	fadeout -> setPosition(sWHeaf, sHHeaf);
	fadeout -> setScale(1.0f);
	fadeout -> setAlpha(0.0f);

	floar -> setPosition(sWHeaf, sHHeaf);
	floar -> setScale(1.0f);

	title_book -> setPosition(sWHeaf - 250, sHHeaf);
	title_book -> setScale(1.0f);

	title_logo -> setPosition(sWHeaf + 25, sHHeaf + 150);
	title_logo -> setScale(0.5f);

	title_start -> setPosition(sWHeaf + 25, sHHeaf - 50);
	title_start -> setScale(1.0f);

	title_end -> setPosition(sWHeaf + 25, sHHeaf - 150);
	title_end -> setScale(1.0f);

	counter = 0;
	anime_number = 0;
	size = 1;
	title_work = Choose;

	switch( sound -> getState())
	{
	case LibSound::Play:
		break;
	}

	// もしくは

	if( sound -> getState() == LibSound::Play)
	{

	}
}


//更新
void Title::update(void)
{
	floar -> draw();

	switch (title_work)
	{
	case Choose:
		title_book -> draw(0);
		title_logo -> draw();
		title_start -> draw();
		title_end -> draw();

		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter++;
			//SE再生;
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
		if (counter % 2 == 1)
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

		fadeout -> draw();
		fadeout -> setAlpha(fadeout -> getAlpha() + 5);
		
		if(size >= 1.8f)
		{
			size = 1.8f;
		}
		else
		{
			size += 0.01f;
		}

		if(fadeout -> getAlpha() == 255)
		{
			fadeout -> setAlpha(255);
			title_work = Next;
		}
		break;
	case Next:
		sound -> allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
		break;

	}
}