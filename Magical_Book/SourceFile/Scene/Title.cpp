
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Title.h"


using namespace CatGameLib;
using namespace MagicalBook;


ResourceManager* instance = ResourceManager::getInstance();


Title::Title() : title_logo(nullptr),
				 title_start(nullptr),
				 title_end(nullptr)
{
	title_logo  = LibSprite::create("logo/title_logo.png");
	title_start = LibSprite::create("logo/title_start.png");
	title_end	= LibSprite::create("logo/title_end.png");
}


Title::~Title()
{
}


//������
void Title::init(void)
{
	input = LibInput::getInstance();

	//����
	title_bgm = LibSound::create("bgm/title.wav");
	title_bgm -> setVolume(1.0f);
	title_bgm -> setLoop(true);

	instance -> getSound("menuSelect") -> setVolume(1.0f);

	game_in = LibSound::create("se/in.wav");
	game_in -> setVolume(1.0f);


	//�摜
	instance ->getSprite("fadeout") -> setPosition(sWHeaf, sHHeaf);
	instance ->getSprite("fadeout") -> setScale(1.0f);
	instance ->getSprite("fadeout") -> setAlpha(0.0f);

	instance ->getSprite("floar") -> setPosition(sWHeaf, sHHeaf);
	instance ->getSprite("floar") -> setScale(1.0f);

	instance -> getSprites("openBook") -> setPosition(sWHeaf - 250, sHHeaf);
	instance -> getSprites("openBook") -> setScale(1.0f);

	title_logo -> setPosition(sWHeaf + 25, sHHeaf + 150);
	title_logo -> setScale(0.5f);

	title_start -> setPosition(sWHeaf + 25, sHHeaf - 50);
	title_start -> setScale(1.0f);

	title_end -> setPosition(sWHeaf + 25, sHHeaf - 150);
	title_end -> setScale(0.7f);

	timer = 0;
	counter = 0;
	flag = 0;
	volumeFlag = 0;
	anime_number = BOOK_ANM_MIN;
	size = 1;
	Volume = 1;

	title_work = Select;
}


//�X�V
void Title::update(void)
{
	instance ->getSprite("floar") -> draw();

	if(title_bgm -> getState() != LibSound::Play)
	{
		title_bgm -> play();
	}

	if(volumeFlag == 1)
	{
		Volume -= 0.02f;
		title_bgm -> setVolume(Volume);
	}

	switch (title_work)
	{
	case Select:
		select();
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


void Title::logoAnimation(void)
{
	timer++;

	if(timer % 3 == 0)
	{
		if(size <= 1.2 && flag == 0)
		{
			if(size >= 1.1)
			{
				flag = 1;
				timer = 0;
			}

			size += 0.01f;
		}
		else if(size >= 0.8 && flag == 1)
		{
			if(size <= 0.9)
			{
				flag = 0;
				timer = 0;
			}

			size -= 0.01;
		}
	}
}

void Title::bookAnimation(void)
{
	if(anime_number < BOOK_ANM_MAX)
	{
		counter++;
		if(counter % 7 == 0)
		{
			counter = 0;
			anime_number++;
		}
	}
}

void Title::select(void)
{
	instance -> getSprites("openBook") -> draw(anime_number);
	title_logo -> draw();
	title_start -> draw();
	title_end -> draw();

	if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		timer = 0;
		counter++;
		flag = 0;
		size = 1;
		instance -> getSound("menuSelect") -> play();
	}

	if(counter >= 2)
	{
		counter = 0;
	}

	if (counter % 2 == 0)
	{
		//�Q�[���{��
		title_start -> setScale(size);
		title_end -> setScale(0.7f);

		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			timer = 0;
			counter = 0;
			size = 1;
			flag = 0;
			title_work = Animation;
		}
	}
	else if (counter % 2 == 1)
	{
		//�Q�[���I��
		title_start -> setScale(0.7f);
		title_end -> setScale(size);

		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			exit(0);
		}
	}
}

void Title::animation(void)
{
	instance -> getSprites("openBook") -> draw(anime_number);

	volumeFlag = 1;

	bookAnimation();

	if (instance -> getSprites("openBook") -> getPositionX() >= sWHeaf)
	{
		instance -> getSprites("openBook") -> setPositionX(sWHeaf);
		if(anime_number == BOOK_ANM_MAX)
		{
			title_work = Fadeout;
		}
	}
	else
	{
		instance -> getSprites("openBook") -> setPositionX(instance -> getSprites("openBook") -> getPositionX() + 10);
	}
}

void Title::fadeout(void)
{
	instance -> getSprites("openBook") -> draw(BOOK_ANM_MAX);
	instance -> getSprites("openBook") -> setScale(size);

	instance ->getSprite("fadeout") -> draw();
	instance ->getSprite("fadeout") -> setAlpha(instance ->getSprite("fadeout") -> getAlpha() + 5);
	if(instance ->getSprite("fadeout") -> getAlpha() >= 255)
	{
		instance ->getSprite("fadeout") -> setAlpha(255);
	}

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
		size += 0.02f;
	}
}

void Title::next(void)
{
	LibSound::allStop();
	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
}
