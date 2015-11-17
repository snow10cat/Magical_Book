
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "MenuSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


MenuSelect::MenuSelect() : select_bgm(nullptr),
						   play(nullptr),
						   make(nullptr)
{
	
	select_bgm = LibSound::create("bgm/menuselect.wav");
	play = LibSprite::create("logo/play.png");
	make = LibSprite::create("logo/make.png");
}


MenuSelect::~MenuSelect()
{
}


void MenuSelect::init(void)
{
	input = LibInput::getInstance();

	select_bgm -> setVolume(0.0f);
	select_bgm -> setLoop(true);


	instance ->getSprite("fadeout") -> setAlpha(255);

	books = instance -> getSprites("books");

	books -> setPosition(sWHeaf + 300, sHHeaf);
	books -> setScale(1.5f);

	instance -> getSprites("openBook") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("openBook") -> setScale(1.5f);

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(1.3f);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(1.0f);
	make -> setAlpha(0.0f);

	instance -> getSprite("back") -> setPosition(sWHeaf - 100, sHHeaf - 200);
	instance -> getSprite("back") -> setScale(1.0f);
	instance -> getSprite("back") -> setAlpha(0.0f);

	timer = 0;
	counter = 0;
	flag = 0;
	fadeFlag = 0;
	volumeFlag = 0;
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

	if(volumeFlag == 1)
	{
		Volume -= 0.02f;
		select_bgm -> setVolume(Volume);
	}
	else if(Volume <= 1.0 && volumeFlag == 0)
	{
		Volume += 0.02f;
		select_bgm -> setVolume(Volume);
	}

	instance -> getSprite("floar") -> draw();

	switch(select_work)
	{
	case Fadein:
		if(SceneManager::getInstance() -> getOldSceneNumber() == SceneManager::SceneNumber::Title)
		{
			fadein();
		}
		else
		{
			books -> draw(0);
			play -> draw();
			make -> draw();
			instance -> getSprite("back") -> draw();
			select_work = ModeSelect;
		}
		break;
	case ModeSelect:
		modeSelect();
		break;
	case Animation:
		animation();
		break;
	case Fadeout:
		fadeout();
		break;
	case Next:
		next();
		break;
	default:
		assert(!"�s���ȏ��");
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
		instance -> getSprite("back") -> draw();
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
	counter = CatGameLib::LibBasicFunc::wrap(counter, 0, 3);

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

		if(instance -> getSprite("back")-> getAlpha() < 255)
		{
			instance -> getSprite("back") -> setAlpha(instance -> getSprite("back") -> getAlpha() + 5);
		}
		instance -> getSprite("back") -> draw();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
		{
			timer = 0;
			counter--;
			flag = 0;
			size = 1.3;
			instance -> getSound("menuSelect") -> play();
		}
		else if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
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
			//�Q�[���{��
			play -> setScale(size);
			make -> setScale(1.0f);
			instance -> getSprite("back") -> setScale(1.0f);

			logoAnimation();

			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				timer = 0;
				size = 1.3;
				flag = 0;
				play -> setAlpha(0.0f);
				make -> setAlpha(0.0f);
				instance -> getSprite("back") -> setAlpha(0.0f);
				select_work = Animation;
			}
		}
		else if (counter % 3 == 1)
		{
			//�Q�[���G�f�B�b�g
			play -> setScale(1.0f);
			make -> setScale(size);
			instance -> getSprite("back") -> setScale(1.0f);

			logoAnimation();

			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				timer = 0;
				size = 1.3;
				flag = 0;
				play -> setAlpha(0.0f);
				make -> setAlpha(0.0f);
				instance -> getSprite("back") -> setAlpha(0.0f);
				select_work = Animation;
			}
		}
		else
		{
			play -> setScale(1.0f);
			make -> setScale(1.0f);
			instance -> getSprite("back") -> setScale(size);

			logoAnimation();

			if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
			{
				anime_number = BOOK_ANM_MAX;
				counter = 0;
				size = 1.5f;
				bookAnmFlag = 1;
			}
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

		if(anime_counter % 7 == 0)
		{
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
	
	volumeFlag = 1;


	if(counter == 0)
	{
		bookAnimation();

		if(anime_number == BOOK_ANM_MAX)
		{
			anime_number = BOOK_ANM_MIN;
			anime_counter = 0;
			select_work = Next;
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
			select_work = Next;
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
	}
}


void MenuSelect::next(void)
{
	if(counter == 0)
	{
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::StageSelect);
	}
	else if(counter == 1)
	{
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}
}