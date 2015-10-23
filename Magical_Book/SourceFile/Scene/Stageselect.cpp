
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Stageselect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


Stageselect::Stageselect() : frame(nullptr),
							 play(nullptr),
							 make(nullptr),
							 back(nullptr),
							 arrow_right(nullptr),
							 arrow_left(nullptr)
{
	frame = LibSprite::create("background/frame.png");
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

	books = instance -> getSprites("books");

	instance -> getSprites("books") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);

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

	frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
	frame -> setScale(0.35f);
	frame -> setAlpha(0.0f);

	play -> setPosition(sWHeaf - 100, sHHeaf + 100);
	play -> setScale(1.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf - 100);
	make -> setScale(1.0f);

	back -> setPosition(sWHeaf + 500, sHHeaf - 300);
	back -> setScale(1.0f);

	arrow_right -> setPosition(sWHeaf + 150, sHHeaf - 310);
	arrow_right -> setScale(0.3f);

	arrow_left -> setPosition(sWHeaf - 270, sHHeaf - 310);
	arrow_left -> setScale(0.3f);

	timer = 0;
	counter = 0;
	flag = 0;
	anime_number = 0;
	anime_counter = 0;
	Volume = 0;
	size = 1.3;
	select_work = ModeSelect;
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

	if(Volume <= 1.0)
	{
		Volume += 0.02f;
		select_bgm -> setVolume(Volume);
	}
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
		gameModeDraw();
		gameMode();
	//	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
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
	books -> draw(0);

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
		//�Q�[���{��
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
		//�Q�[���{��
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
	books -> draw(anime_number);

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
	if(timer >= 10)
	{
		

		
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
	}
	else
	{
		timer++;
	}
}


void Stageselect::gameModeDraw(void)
{
	instance -> getSprites("books") -> draw(anime_number);

	back -> draw();
	arrow_right -> draw();
	arrow_left -> draw();

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


void Stageselect::editMode(void)
{
	instance -> getSprites("books") -> draw(anime_number);
}


void Stageselect::editModeDraw(void)
{

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