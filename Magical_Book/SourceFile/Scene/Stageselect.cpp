
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Stageselect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


Stageselect::Stageselect() : play(nullptr),
							 make(nullptr),
							 arrow_right(nullptr),
							 arrow_left(nullptr)
{
	play = LibSprite::create("logo/play.png");
	make = LibSprite::create("logo/make.png");
	arrow_right = LibSprite::create("logo/arrow_right.png");
	arrow_left = LibSprite::create("logo/arrow_left.png");
}


Stageselect::~Stageselect()
{
}


void Stageselect::init(void)
{
	input = LibInput::getInstance();

	instance -> getSound("selectbgm") -> setVolume(0.0f);
	instance -> getSound("selectbgm") -> setLoop(true);


	instance ->getSprite("fadeout") -> setAlpha(255);

	books = instance -> getSprites("books");

	instance -> getSprites("books") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);

	instance -> getSprites("openBook") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("openBook") -> setScale(1.5f);

	for(int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back(instance -> getSprite(bgName.c_str()));
		bgTextures[i - 1] -> setAlpha(0.0f);
	}

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 210, sHHeaf + 160);
	bgTextures[ResourceManager::BG_Castle] -> setScale(0.35f);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf + 90, sHHeaf + 160);
	bgTextures[ResourceManager::BG_Table] -> setScale(0.3f);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf - 210, sHHeaf - 140);
	bgTextures[ResourceManager::BG_Gate] -> setScale(0.3f);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 90, sHHeaf - 140);
	bgTextures[ResourceManager::BG_Window] -> setScale(0.3f);

	instance -> getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf + 160);
	instance -> getSprite("frame") -> setScale(0.35f);
	instance -> getSprite("frame") -> setAlpha(0.0f);

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(1.3f);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(1.0f);
	make -> setAlpha(0.0f);

	instance -> getSprite("back") -> setPosition(sWHeaf + 500, sHHeaf - 300);
	instance -> getSprite("back") -> setScale(1.0f);
	instance -> getSprite("back") -> setAlpha(0.0f);

	arrow_right -> setPosition(sWHeaf + 150, sHHeaf - 310);
	arrow_right -> setScale(0.3f);
	arrow_right -> setAlpha(0.0f);
	arrow_left -> setPosition(sWHeaf - 270, sHHeaf - 310);
	arrow_left -> setScale(0.3f);
	arrow_left -> setAlpha(0.0f);

	timer = 0;
	counter = 0;
	flag = 0;
	fadeFlag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;
	Volume = 0;
	volumeFlag = 0;
	size = 1.3;
	select_work = GameMode;
}



void Stageselect::update(void)
{
	if(instance -> getSound("selectbgm") -> getState() != LibSound::Play)
	{
		instance -> getSound("selectbgm") -> play();
	}

	if(volumeFlag == 1)
	{
		Volume -= 0.02f;
		instance -> getSound("selectbgm") -> setVolume(Volume);
	}
	else if(Volume <= 1.0 && volumeFlag == 0)
	{
		Volume += 0.02f;
		instance -> getSound("selectbgm") -> setVolume(Volume);
	}

	instance -> getSprite("floar") -> draw();

	switch(select_work)
	{
	case GameMode:
		gameMode();
		break;
	case Back:
		backAnimation();
		break;
	case Fadeout:
		bookAnimation();
		fadeout();
		break;
	case Next:
		next();
		break;
	default:
		assert(!"ïsê≥Ç»èÛë‘");
		break;
	}
}


void Stageselect::bookAnimation()
{
	if(anime_number <= BOOK_ANM_MAX)
	{
		anime_counter++;
		if(anime_counter % 7 == 0)
		{
			anime_counter = 0;
			anime_number++;
		}
	}
}


void Stageselect::gameMode(void)
{
	gameModeDraw();
	if(timer >= 10)
	{
		gameSelect();
	}
	else
	{
		timer++;
	}
}


void Stageselect::gameSelect(void)
{
	const int counterNumber = CatGameLib::LibBasicFunc::wrap(counter, 0, 6);

	counter = CatGameLib::LibBasicFunc::wrap(counter, 0, 6);

	if(flag != 6)
	{
		flag = counterNumber;

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
		{
			counter -= 2;
		}
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter += 2;
		}

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
		{
			if(counterNumber % 2)
			{
				counter--;
			}
			else
			{
				flag = 6;
			}
		}

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
		{
			if(counterNumber % 2)
			{
				flag = 6;
			}
			else
			{
				counter++;
			}
		}

		if (bookAnmFlag == 0 && flag != 4 && flag != 5 && input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			instance ->getSprite("fadeout") -> setAlpha(0);
			select_work = Fadeout;
		}
	}
	else
	{
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
		{
			if(counter % 2 == 0)
			{
				counter++;
				flag = counter;
			}
			else
			{
				flag = counter;
			}
		}
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
		{
			if(counter % 2 == 0)
			{
				flag = counter;
			}
			else
			{
				counter--;
				flag = counter;
			}
		}
	}


	if(flag == 6)
	{
		if (bookAnmFlag == 0 && input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
			bookAnmFlag = 1;
			anime_number = BOOK_ANM_MAX;
		}

		if(bookAnmFlag == 1)
		{
			volumeFlag = 1;
			backAnimation();
			if(anime_number == BOOK_ANM_MIN)
			{
				bookAnmFlag = 0;
				instance -> getSprite("back") -> setPosition(sWHeaf - 100, sHHeaf - 200);

				LibSound::allStop();
				SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
			}
		}
	}
}


void Stageselect::gameModeDraw(void)
{
	instance -> getSprites("books") -> draw(anime_number);

	auto sizeResetFunc = [&](void)
	{
		instance -> getSprite("game_bg1") -> setScale(0.3f);
		instance -> getSprite("game_bg2") -> setScale(0.3f);
		instance -> getSprite("game_bg3") -> setScale(0.3f);
		instance -> getSprite("game_bg4") -> setScale(0.3f);
		
		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.3f);
		instance -> getSprite("back") -> setScale(1.0f);
		instance -> getSprite("frame") -> setScale(0.35f);
	};


	if(anime_number == BOOK_ANM_MIN)
	{
		for(int i = 0; i < bgTextures.size() - 1; i++)
		{
			bgTextures[i] -> draw();

			if(bgTextures[i] -> getAlpha() < 255)
			{
				bgTextures[i] -> setAlpha(bgTextures[i] -> getAlpha() + 5);
			}
		}

		if(instance -> getSprite("back") -> getAlpha() < 255)
		{
			instance -> getSprite("back") -> setAlpha(instance -> getSprite("back") -> getAlpha() + 5);
		}
		instance -> getSprite("back") -> draw();

		if(arrow_right -> getAlpha() < 255)
		{
			arrow_right -> setAlpha(arrow_right -> getAlpha() + 5);
		}
		arrow_right -> draw();

		if(arrow_left -> getAlpha() < 255)
		{
			arrow_left -> setAlpha(arrow_left -> getAlpha() + 5);
		}
		arrow_left -> draw();

		if(instance -> getSprite("frame") -> getAlpha() < 255)
		{
			instance -> getSprite("frame") -> setAlpha(instance -> getSprite("frame") -> getAlpha() + 5);
		}
		instance -> getSprite("frame") -> draw();
	}

	switch(flag)
	{
	case 0:
		sizeResetFunc();

		instance -> getSprite("game_bg1") -> setScale(0.35f);

		instance -> getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf + 160);
		break;
	case 1:
		sizeResetFunc();

		instance -> getSprite("game_bg2") -> setScale(0.35f);

		instance ->getSprite("frame") -> setPosition(sWHeaf + 90, sHHeaf + 160);
		break;
	case 2:
		sizeResetFunc();

		instance -> getSprite("game_bg3") -> setScale(0.35f);

		instance ->getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf - 140);
		break;
	case 3:
		sizeResetFunc();

		instance -> getSprite("game_bg4") -> setScale(0.35f);

		instance ->getSprite("frame") -> setPosition(sWHeaf + 90, sHHeaf - 140);
		break;
	case 4:
		sizeResetFunc();

		arrow_left -> setScale(0.35f);

		instance ->getSprite("frame") -> setScale(0.1f);
		instance ->getSprite("frame") -> setPosition(sWHeaf - 270, sHHeaf - 310);
		break;
	case 5:
		sizeResetFunc();

		arrow_right -> setScale(0.35f);

		instance ->getSprite("frame") ->setScale(0.1f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 150, sHHeaf - 310);
		break;
	case 6:
		sizeResetFunc();

		instance -> getSprite("back") -> setScale(1.2f);
		instance ->getSprite("frame") ->setScaleX(0.35f);
		instance ->getSprite("frame") ->setScaleY(0.12f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 500, sHHeaf - 300);
		break;
	default:
		assert(!"ïsê≥Ç»èÛë‘");
		break;
	}
}


void Stageselect::backAnimation(void)
{
	volumeFlag = 1;
	if(anime_number >= BOOK_ANM_MIN)
	{
		anime_counter++;
		if(anime_counter % 7 == 0)
		{
			anime_counter = 0;
			anime_number--;
		}
	}
}


void Stageselect::fadeout(void)
{
	instance -> getSprites("books") -> draw(anime_number);

	instance ->getSprite("fadeout") -> draw();
	instance ->getSprite("fadeout") -> setAlpha(instance ->getSprite("fadeout") -> getAlpha() + 5);
	if(instance ->getSprite("fadeout") -> getAlpha() >= 255)
	{
		instance ->getSprite("fadeout") -> setAlpha(255);
		if(bookAnmFlag == 0)
		{
			if(anime_number == BOOK_ANM_MAX)
			{
				select_work = Next;
			}
		}
	}
}


void Stageselect::next(void)
{
	LibSound::allStop();
	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
}
