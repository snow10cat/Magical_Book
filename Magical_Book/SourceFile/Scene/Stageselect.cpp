
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Stageselect.h"
#include "MenuSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


Stageselect::Stageselect() : play(nullptr),
							 make(nullptr),
							 back(nullptr),
							 arrow_right(nullptr),
							 arrow_left(nullptr)
{
	play = LibSprite::create("logo/play.png");
	make = LibSprite::create("logo/make.png");
	back = LibSprite::create("logo/back.png");
	arrow_right = LibSprite::create("logo/arrow_right.png");
	arrow_left = LibSprite::create("logo/arrow_left.png");
}


Stageselect::~Stageselect()
{
}


void Stageselect::init(void)
{
	input = LibInput::getInstance();

	select_bgm = LibSound::create("bgm/gameselect.wav");
	select_bgm -> setVolume(0.0f);
	select_bgm -> setLoop(true);


	instance ->getSprite("fadeout") -> setAlpha(255);

	books = instance -> getSprites("books");

	instance -> getSprites("books") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);

	instance -> getSprites("openBook") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("openBook") -> setScale(1.5f);

	for( int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back( instance -> getSprite( bgName.c_str()));
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

	instance ->getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf + 160);
	instance ->getSprite("frame") -> setScale(0.35f);
	instance ->getSprite("frame") -> setAlpha(0.0f);

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(1.3f);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(1.0f);
	make -> setAlpha(0.0f);

	back -> setPosition(sWHeaf + 500, sHHeaf - 300);
	back -> setScale(1.0f);
	back -> setAlpha(0.0f);

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
	size = 1.3;
	select_work = GameMode;
}



void Stageselect::update(void)
{
	if(select_bgm -> getState() != LibSound::Play)
	{
		select_bgm -> play();
	}

	if(select_work >= Fadeout)
	{
		Volume -= 0.02f;
		select_bgm -> setVolume(Volume);
	}

	if(Volume <= 1.0 && select_work < Fadeout)
	{
		Volume += 0.02f;
		select_bgm -> setVolume(Volume);
	}
	instance -> getSprite("floar") -> draw();

	switch(select_work)
	{
	case Fadein:
		fadein();
		break;
	case ModeSelect:
//		select_work = new class::MenuSelect;
	//	modeSelect();
		break;
	case Animation:
		animation();
		break;
	case GameMode:
		gameMode();
	//	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
		break;
	case Back:
		backAnimation();
		break;
	case Fadeout:
		fadeout();
		break;

	case Next:
		break;
	default:
		assert(!"不正な状態");
		break;
	}
}


void Stageselect::fadein(void)
{
	books -> draw(0);

	play -> draw();
	make -> draw();
	back -> draw();

	instance ->getSprite("fadeout") -> draw();
	instance ->getSprite("fadeout") -> setAlpha(instance ->getSprite("fadeout") -> getAlpha() - 5);
	if(instance ->getSprite("fadeout") -> getAlpha() <= 0)
	{
		instance ->getSprite("fadeout") -> setAlpha(0);
		select_work = ModeSelect;
	}
}


void Stageselect::modeSelect(void)
{
	if(bookAnmFlag == 0)
	{
		books -> draw(anime_number);

		if(play-> getAlpha() < 255)
		{
			play -> setAlpha(play -> getAlpha() + 5);
		}
		play -> draw();

		if(make-> getAlpha() < 255)
		{
			make -> setAlpha(make -> getAlpha() + 5);
		}
		make -> draw();

		if(back-> getAlpha() < 255)
		{
			back -> setAlpha(back -> getAlpha() + 5);
		}
		back -> draw();

		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			timer = 0;
			counter++;
			flag = 0;
			size = 1.3;
			instance -> getSound("menuSelect") -> play();
		}

		if(counter >= 3)
		{
			counter = 0;
		}

		if (counter % 3 == 0)
		{
			//ゲーム本編
			play -> setScale(size);
			make -> setScale(1.0f);
			back -> setScale(1.0f);

			logoAnimation();

			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				timer = 0;
				size = 1.3;
				flag = 0;
				play -> setAlpha(0.0f);
				make -> setAlpha(0.0f);
				back -> setAlpha(0.0f);
				back -> setPosition(sWHeaf + 500, sHHeaf - 300);
				select_work = Animation;
			}
		}
		else if (counter % 3 == 1)
		{
			//ゲームエディット
			play -> setScale(1.0f);
			make -> setScale(size);
			back -> setScale(1.0f);

			logoAnimation();

			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				timer = 0;
				size = 1.3;
				flag = 0;
				play -> setAlpha(0.0f);
				make -> setAlpha(0.0f);
				back -> setAlpha(0.0f);
				select_work = Animation;
			}
		}
		else
		{
			play -> setScale(1.0f);
			make -> setScale(1.0f);
			back -> setScale(size);

			logoAnimation();

			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				anime_number = BOOK_ANM_MAX;
				counter = 0;
				size = 1.5f;
				bookAnmFlag = 1;
			}
		}

		if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
		{
			anime_number = BOOK_ANM_MAX;
			counter = 0;
			size = 1.5f;
			bookAnmFlag = 1;
		}
	}
	else if(bookAnmFlag == 1)
	{
		instance -> getSprites("openBook") -> draw(anime_number);
		instance -> getSprites("openBook") -> setScale(size);

		if (instance -> getSprites("openBook") -> getPositionX() <= sWHeaf - 250)
		{
			instance -> getSprites("openBook") -> setPositionX(sWHeaf - 250);
		}
		else
		{
			instance -> getSprites("openBook") -> setPositionX(instance -> getSprites("openBook") -> getPositionX() - 10);
		}

		if(anime_number > BOOK_ANM_MIN)
		{
			closeAnimation();
		}
		counter++;
		if(counter % 7 == 0)
		{
			counter = 0;
			if(size > 1)
			{
				size -= 0.1f;
			}
			else if(size <= 1)
			{
				size = 1.0f;
			}
		}

		if(size == 1.0)
		{
			if(anime_number == BOOK_ANM_MIN)
			{
				LibSound::allStop();
				if(fadeFlag == 0)
				{
					fadeout();
				}
				else
				{
					fadein();
				}


				if(instance ->getSprite("fadeout") -> getAlpha() <= 0)
				{
					SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Title);
				}
				else if(instance ->getSprite("fadeout") -> getAlpha() >= 255)
				{
					fadeFlag = 1;
				}
			}
		}
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


void Stageselect::animation(void)
{
	books -> draw(anime_number);

	if(counter == 0)
	{
		bookAnimation();

		if(anime_number == BOOK_ANM_MAX)
		{
			anime_number = BOOK_ANM_MIN;
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
			select_work = EditMode;
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
	const int even = counterNumber % 2;
	const int odd = counterNumber % 2;

	counter = CatGameLib::LibBasicFunc::wrap(counter, 0, 6);

	if(flag != 6)
	{
		flag = counterNumber;

		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up))
		{
			counter -= 2;
		}
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter += 2;
		}

		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Left))
		{
			if( counterNumber % 2)
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
			if( counterNumber % 2)
			{
				flag = 6;
			}
			else
			{
				counter++;
			}
		}
	}
	else
	{
		if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Left))
		{
			if( counter % 2 == 0)
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
			if( counter % 2 == 0)
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
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
			bookAnmFlag = 1;
			anime_number = BOOK_ANM_MAX;
		}

		if(bookAnmFlag == 1)
		{
			backAnimation();
			if(anime_number == BOOK_ANM_MIN)
			{
				bookAnmFlag = 0;
				back -> setPosition(sWHeaf - 100, sHHeaf - 200);

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

		if(back -> getAlpha() < 255)
		{
			back -> setAlpha(back -> getAlpha() + 5);
		}
		back -> draw();

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

		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.3f);
		back -> setScale(1.0f);
		instance -> getSprite("frame") -> setScale(0.35f);
		instance -> getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf + 160);
		break;
	case 1:
		sizeResetFunc();
		instance -> getSprite("game_bg2") -> setScale(0.35f);

		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.3f);
		back -> setScale(1.0f);
		instance ->getSprite("frame") -> setScale(0.35f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 90, sHHeaf + 160);
		break;
	case 2:
		sizeResetFunc();
		instance -> getSprite("game_bg3") -> setScale(0.35f);

		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.3f);
		back -> setScale(1.0f);
		instance ->getSprite("frame") -> setScale(0.35f);
		instance ->getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf - 140);
		break;
	case 3:
		sizeResetFunc();
		instance -> getSprite("game_bg4") -> setScale(0.35f);

		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.3f);
		back -> setScale(1.0f);
		instance ->getSprite("frame") -> setScale(0.35f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 90, sHHeaf - 140);
		break;
	case 4:
		sizeResetFunc();
		arrow_left -> setScale(0.35f);
		arrow_right -> setScale(0.3f);
		back -> setScale(1.0f);
		instance ->getSprite("frame") -> setScale(0.1f);
		instance ->getSprite("frame") -> setPosition(sWHeaf - 270, sHHeaf - 310);
		break;
	case 5:
		sizeResetFunc();
		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.35f);
		back -> setScale(1.0f);
		instance ->getSprite("frame") ->setScale(0.1f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 150, sHHeaf - 310);
		break;
	case 6:
		sizeResetFunc();
		arrow_left -> setScale(0.3f);
		arrow_right -> setScale(0.3f);
		back -> setScale(1.2f);
		instance ->getSprite("frame") ->setScaleX(0.4f);
		instance ->getSprite("frame") ->setScaleY(0.12f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 500, sHHeaf - 300);
		break;
	default:
		assert(!"不正な状態");
		break;
	}
}


void Stageselect::backAnimation(void)
{
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


void Stageselect::closeAnimation(void)
{
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
	instance ->getSprite("fadeout") -> draw();
	instance ->getSprite("fadeout") -> setAlpha(instance ->getSprite("fadeout") -> getAlpha() + 5);
	if(instance ->getSprite("fadeout") -> getAlpha() >= 255)
	{
		instance ->getSprite("fadeout") -> setAlpha(255);
		if(bookAnmFlag == 0)
		{
			select_work = Next;
		}
	}
}


void Stageselect::next(void)
{
}
