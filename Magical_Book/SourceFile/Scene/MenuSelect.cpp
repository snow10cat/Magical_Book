
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "MenuSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


MenuSelect::MenuSelect() : frame(nullptr),
							 play(nullptr),
							 make(nullptr),
							 back(nullptr),
							 arrow_right(nullptr),
							 arrow_left(nullptr)
{
	play = LibSprite::create("logo/play.png");
	make = LibSprite::create("logo/make.png");
	back = LibSprite::create("logo/back.png");
}


MenuSelect::~MenuSelect()
{
}


void MenuSelect::init(void)
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

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(1.3f);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(1.0f);
	make -> setAlpha(0.0f);

	back -> setPosition(sWHeaf - 100, sHHeaf - 200);
	back -> setScale(1.0f);
	back -> setAlpha(0.0f);

	timer = 0;
	counter = 0;
	flag = 0;
	fadeFlag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;
	Volume = 0;
	size = 1.3;
	select_work = Fadein;
}



void MenuSelect::update(void)
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
		modeSelect();
		break;
	case Animation:
		animation();
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


void MenuSelect::fadein(void)
{
	if(bookAnmFlag == 0)
	{
		books -> draw(0);

		play -> draw();
		make -> draw();
		back -> draw();
	}

	instance ->getSprite("fadeout") -> draw();
	instance ->getSprite("fadeout") -> setAlpha(instance ->getSprite("fadeout") -> getAlpha() - 5);
	if(instance ->getSprite("fadeout") -> getAlpha() <= 0)
	{
		instance ->getSprite("fadeout") -> setAlpha(0);
		if(bookAnmFlag == 0)
		{
			select_work = ModeSelect;
		}
	}
}


void MenuSelect::modeSelect(void)
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


void MenuSelect::logoAnimation()
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


void MenuSelect::animation(void)
{
	books -> draw(anime_number);

	if(counter == 0)
	{
		bookAnimation();

		if(anime_number == BOOK_ANM_MAX)
		{
			anime_number = BOOK_ANM_MIN;
			anime_counter = 0;
//			select_work = GameMode;
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
		//	select_work = EditMode;
		}
	}
}


void MenuSelect::bookAnimation()
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


void MenuSelect::backAnimation(void)
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


void MenuSelect::closeAnimation(void)
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


void MenuSelect::fadeout(void)
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


void MenuSelect::next(void)
{
	select_work = Animation;
}