
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "StageSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


StageSelect::StageSelect() : arrow_right(nullptr),
							 arrow_left(nullptr)
{
	arrow_right = LibSprite::create("logo/arrow_right.png");
	arrow_left = LibSprite::create("logo/arrow_left.png");
}


StageSelect::~StageSelect()
{
}


void StageSelect::init(void)
{
	input = LibInput::getInstance();

	selectBgm = instance -> getSound("selectbgm");
	menuSelect = instance -> getSound("menuSelect");

	fade = instance ->getSprite("fade");
	floor = instance ->getSprite("floor");
	books = instance -> getSprites("books");
	frame = instance -> getSprite("frame");
	back = instance -> getSprite("back");

	volume = 0;
	volumeFlag = true;

	timer = 0;
	counter = 0;
	flag = 0;
	fadeFlag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;
	size = 1.3;

	//音声
	selectBgm -> setVolume(0.0f);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(1.0f);

	//画像
	fade -> setAlpha(255);

	books -> setPosition(sWHeaf + 300, sHHeaf);
	books -> setScale(1.5f);

	frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
	frame -> setScale(0.35f);
	frame -> setAlpha(0.0f);

	arrow_right -> setPosition(sWHeaf + 150, sHHeaf - 310);
	arrow_right -> setScale(0.3f);
	arrow_right -> setAlpha(0.0f);

	arrow_left -> setPosition(sWHeaf - 270, sHHeaf - 310);
	arrow_left -> setScale(0.3f);
	arrow_left -> setAlpha(0.0f);

	back -> setPosition(sWHeaf + 500, sHHeaf - 300);
	back -> setScale(1.0f);
	back -> setAlpha(0.0f);

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

	//ステージ選択から
	select_work = GameMode;
}



void StageSelect::update(void)
{
	playSound();

	stageSelectDraw();

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
		assert(!"不正な状態");
		break;
	}
}


void StageSelect::playSound(void)
{
	if(selectBgm -> getState() != LibSound::Play)
	{
		selectBgm -> play();
	}

	if(volumeFlag == false)
	{
		//フェードアウト
		volume -= 0.02f;
		selectBgm -> setVolume(volume);
	}
	else if(volume <= 1.0 && volumeFlag == true)
	{
		//フェードイン
		volume += 0.02f;
		selectBgm -> setVolume(volume);
	}
}


void  StageSelect::stageSelectDraw(void)
{
	floor -> draw();

}


void StageSelect::bookAnimation(void)
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


void StageSelect::gameMode(void)
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


void StageSelect::gameSelect(void)
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
			instance ->getSprite("fade") -> setAlpha(0);
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
			volumeFlag = false;
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


void StageSelect::gameModeDraw(void)
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

		instance ->getSprite("frame") -> setScale(0.1f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 150, sHHeaf - 310);
		break;
	case 6:
		sizeResetFunc();

		instance -> getSprite("back") -> setScale(1.2f);
		instance ->getSprite("frame") -> setScaleX(0.35f);
		instance ->getSprite("frame") -> setScaleY(0.12f);
		instance ->getSprite("frame") -> setPosition(sWHeaf + 500, sHHeaf - 300);
		break;
	default:
		assert(!"不正な状態");
		break;
	}
}


void StageSelect::backAnimation(void)
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


void StageSelect::fadeout(void)
{
	instance -> getSprites("books") -> draw(anime_number);

	instance ->getSprite("fade") -> draw();
	instance ->getSprite("fade") -> setAlpha(instance ->getSprite("fade") -> getAlpha() + 5);
	if(instance ->getSprite("fade") -> getAlpha() >= 255)
	{
		instance ->getSprite("fade") -> setAlpha(255);
		if(bookAnmFlag == 0)
		{
			if(anime_number == BOOK_ANM_MAX)
			{
				select_work = Next;
			}
		}
	}
}


void StageSelect::next(void)
{
	LibSound::allStop();
	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
}
