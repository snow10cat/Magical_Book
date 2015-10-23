
#include "../Game/SpriteManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Stageselect.h"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

static SpriteManager* instance = SpriteManager::getInstance();

Stageselect::Stageselect() : frame(nullptr),
							 play(nullptr),
							 make(nullptr),
							 back(nullptr)
{
	frame = LibSprite::create("background/frame.png");
	play = LibSprite::create("logo/play.png");
	make = LibSprite::create("logo/make.png");
	back = LibSprite::create("logo/back.png");
}


Stageselect::~Stageselect()
{
}


void Stageselect::init(void)
{
	input = LibInput::getInstance();

	LibSprites* books = instance -> getSprites("books");

	instance -> getSprites("books") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);

	for( int i = 1; i <= SpriteManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back( instance -> getSprite( bgName.c_str()));
		bgTextures[i - 1] -> setAlpha(0.0f);
	}

	bgTextures[SpriteManager::BG_Castle] -> setPosition(sWHeaf - 210, sHHeaf + 160);
	bgTextures[SpriteManager::BG_Castle] -> setScale(0.35f);

	bgTextures[SpriteManager::BG_Table] -> setPosition(sWHeaf + 90, sHHeaf + 160);
	bgTextures[SpriteManager::BG_Table] -> setScale(0.3f);

	bgTextures[SpriteManager::BG_Gate] -> setPosition(sWHeaf - 210, sHHeaf - 140);
	bgTextures[SpriteManager::BG_Gate] -> setScale(0.3f);

	bgTextures[SpriteManager::BG_Window] -> setPosition(sWHeaf + 90, sHHeaf - 140);
	bgTextures[SpriteManager::BG_Window] -> setScale(0.3f);

	frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
	frame -> setScale(0.35f);
	frame -> setAlpha(0.0f);

	play -> setPosition(sWHeaf - 100, sHHeaf + 100);
	play -> setScale(1.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf - 100);
	make -> setScale(1.0f);

	timer = 0;
	counter = 0;
	flag = 0;
	anime_number = 0;
	anime_counter = 0;
	size = 1.3;
	select_work = ModeSelect;
}



void Stageselect::update(void)
{
	
	
	instance -> getSprite("floar") -> draw();

	switch(select_work)
	{
	case ModeSelect:
		modeSelect();
		break;
	case Animation:
		animation();
		break;
	case GameMode:
		//gameMode();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
		break;
	case EditMode:
		editMode();
		break;
	case Back:
		backAnimation();
		break;
	case Fadeout:
		break;

	case Next:
		break;
	}
}


void Stageselect::logoAnimation()
{
	timer++;

	if(timer % 3 == 0)
	{
		if(size <= 1.5 && flag == 0)
		{
			if(size >= 1.4)
			{
				flag = 1;
				timer = 0;
			}
			
			size += 0.01f;
		}
		else if(size >= 1.1 && flag == 1)
		{
			if(size <= 1.2)
			{	
				flag = 0;
				timer = 0;
			}
			
			size -= 0.01;
		}
	}
}


void Stageselect::bookAnimation()
{
	if(anime_number <= BOOK_ANM_MAX)
	{
		anime_counter++;
		if(anime_counter % 7 == 0)
		{
			anime_number++;
		}
	}
}

void Stageselect::modeSelect(void)
{
	instance -> getSprites("books") -> draw(0);

	play -> draw();
	make -> draw();

	if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		timer = 0;
		counter++;
		flag = 0;
		size = 1.3;
	//	select_se -> play();
	}

	if(counter >= 2)
	{
		counter = 0;
	}

	if (counter % 2 == 0)
	{
		//ƒQ[ƒ€–{•Ò
		play -> setScale(size);
		make -> setScale(1.0f);

		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			timer = 0;
			size = 1.3;
			flag = 0;
			select_work = Animation;
		}
	}
	else if (counter % 2 == 1)
	{
		//ƒQ[ƒ€–{•Ò
		play -> setScale(1.0f);
		make -> setScale(size);
		
		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			timer = 0;
			size = 1.3;
			flag = 0;
			select_work = Animation;
		}
	}
}


void Stageselect::animation(void)
{
	instance -> getSprites("books") -> draw(anime_number);

	if(counter == 0)
	{
		bookAnimation();

		if(anime_number == BOOK_ANM_MAX)
		{
			counter = 0;
			anime_number = 0;
			anime_counter = 0;
			select_work = GameMode;
		}
	}
	else if(counter == 1)
	{
		if (books -> getPositionX() > sWHeaf - 320)
		{
			books -> setPositionX(books -> getPositionX() - 10);
		}
		else
		{
			books -> setPositionX(sWHeaf - 320);
			counter = 0;
			select_work = EditMode;
		}
	}
}


void Stageselect::gameMode(void)
{
	instance -> getSprites("books") -> draw(anime_number);

	if(timer >= 10)
	{
		for( int i = 0; i < bgTextures.size() - 1; i++)
		{
			bgTextures[i] -> draw();

			if(bgTextures[i] -> getAlpha() < 255)
			{
				bgTextures[i] -> setAlpha(bgTextures[i] -> getAlpha() + 5);
			}
		}
		frame -> draw();
		if( frame-> getAlpha() < 255)
		{
			frame -> setAlpha(frame -> getAlpha() + 5);
		}

		
		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Left))
		{
			counter--;
		}
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
		{
			counter++;
		}
		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter += 2;
		}
	
		if (counter % 4 == 0)
		{
			flag = 0;
			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				counter = 0;
			}
		}
		else if (counter % 4 == 1)
		{
			flag = 1;
			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				counter = 0;
			}
		}
		else if (counter % 4 == 2)
		{
			flag = 2;
			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				counter = 0;
			}
		}
		else if (counter % 4 == 3)
		{
			flag = 3;
			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				counter = 0;
			}
		}
	
		if(flag == 0)
		{
			instance -> getSprite("game_bg1") -> setScale(0.35f);
			instance -> getSprite("game_bg2") -> setScale(0.3f);
			instance -> getSprite("game_bg3") -> setScale(0.3f);
			instance -> getSprite("game_bg4") -> setScale(0.3f);
			frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
		}
		else if(flag == 1)
		{
			instance -> getSprite("game_bg1") -> setScale(0.3f);
			instance -> getSprite("game_bg2") -> setScale(0.35f);
			instance -> getSprite("game_bg3") -> setScale(0.3f);
			instance -> getSprite("game_bg4") -> setScale(0.3f);
			frame -> setPosition(sWHeaf + 90, sHHeaf + 160);
		}
		else if(flag == 2)
		{
			instance -> getSprite("game_bg1") -> setScale(0.3f);
			instance -> getSprite("game_bg2") -> setScale(0.3f);
			instance -> getSprite("game_bg3") -> setScale(0.35f);
			instance -> getSprite("game_bg4") -> setScale(0.3f);
			frame -> setPosition(sWHeaf - 210, sHHeaf - 140);
		}
		else if(flag == 3)
		{
			instance -> getSprite("game_bg1") -> setScale(0.3f);
			instance -> getSprite("game_bg2") -> setScale(0.3f);
			instance -> getSprite("game_bg3") -> setScale(0.3f);
			instance -> getSprite("game_bg4") -> setScale(0.35f);
			frame -> setPosition(sWHeaf + 90, sHHeaf - 140);
		}

	}
	else
	{
		timer++;
	}
}


void Stageselect::editMode(void)
{
	instance -> getSprites("books") -> draw(anime_number);
}


void Stageselect::backAnimation(void)
{
	if(anime_number >= BOOK_ANM_MIN)
	{
		anime_counter++;
		if(anime_counter % 7 == 0)
		{
			anime_number--;
		}
	}
}


void Stageselect::fadeout(void)
{
}


void Stageselect::next(void)
{
}