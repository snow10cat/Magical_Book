
#include <cassert>
#include "../Game/ResourceManager.h"
#include "../Game/StageConfig.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "EditSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();
static StageConfig* stageConfig = StageConfig::getInstance();


EditSelect::EditSelect() : size_section(nullptr),
						   bg_section(nullptr),
						   music_section(nullptr)
{
	size_section = CatGameLib::LibSprite::create("logo/size_section.png");
	bg_section = CatGameLib::LibSprite::create("logo/bg_section.png");
	music_section = CatGameLib::LibSprite::create("logo/music_section.png");

	size_logo[0] = CatGameLib::LibSprite::create("logo/S.png");
	size_logo[1] = CatGameLib::LibSprite::create("logo/M.png");
	size_logo[2] = CatGameLib::LibSprite::create("logo/L.png");

	bgm_logo[0] = CatGameLib::LibSprite::create("logo/bgm1.png");
	bgm_logo[1] = CatGameLib::LibSprite::create("logo/bgm2.png");
	bgm_logo[2] = CatGameLib::LibSprite::create("logo/bgm3.png");
}


EditSelect::~EditSelect()
{
}


void EditSelect::init(void)
{
	input = LibInput::getInstance();

	instance -> getSound("selectbgm") -> setVolume(0.0f);
	instance -> getSound("selectbgm") -> setLoop(true);

	instance -> getSprites("books") -> setPosition(sWHeaf - 320, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);


	size_logo[0] -> setPosition(sWHeaf - 100, sHHeaf + 200);
	size_logo[0] -> setScale(0.35f);
	size_logo[0] -> setAlpha(0.0f);

	size_logo[1] -> setPosition(sWHeaf + 50, sHHeaf + 200);
	size_logo[1] -> setScale(0.25f);
	size_logo[1] -> setAlpha(0.0f);

	size_logo[2] -> setPosition(sWHeaf + 200, sHHeaf + 200);
	size_logo[2] -> setScale(0.25f);
	size_logo[2] -> setAlpha(0.0f);


	bgm_logo[0] -> setPosition(sWHeaf - 100, sHHeaf - 220);
	bgm_logo[0] -> setScale(0.25f);
	bgm_logo[0] -> setAlpha(0.0f);

	bgm_logo[1] -> setPosition(sWHeaf + 50, sHHeaf - 220);
	bgm_logo[1] -> setScale(0.25f);
	bgm_logo[1] -> setAlpha(0.0f);

	bgm_logo[2] -> setPosition(sWHeaf + 200, sHHeaf - 220);
	bgm_logo[2] -> setScale(0.25f);
	bgm_logo[2] -> setAlpha(0.0f);

	for(int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back(instance -> getSprite(bgName.c_str()));
		bgTextures[i - 1] -> setAlpha(0.0f);
	}

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 100, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Castle] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf - 25, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Table] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf + 50, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Gate] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 125, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Window] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Throne] -> setPosition(sWHeaf + 200, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Throne] -> setScale(0.1f);

	instance -> getSprite("frame") -> setPosition(sWHeaf - 100, sHHeaf + 200);
	instance -> getSprite("frame") -> setScale(0.15f);
	instance -> getSprite("frame") -> setAlpha(0.0f);

	size_section -> setPosition(sWHeaf - 100, sHHeaf + 300);
	size_section -> setScale(0.8f);
	size_section -> setAlpha(0.0f);

	bg_section -> setPosition(sWHeaf - 100, sHHeaf + 80);
	bg_section -> setScale(0.7f);
	bg_section -> setAlpha(0.0f);

	music_section -> setPosition(sWHeaf - 100, sHHeaf - 140);
	music_section -> setScale(0.7f);
	music_section -> setAlpha(0.0f);

	instance -> getSprite("back") -> setPosition(sWHeaf - 500, sHHeaf - 280);
	instance -> getSprite("back") -> setScale(0.7f);
	instance -> getSprite("back") -> setAlpha(0.0f);

	sizeCounter = 1;
	bgCounter = 1;
	bgmCounter = 1;
	flag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;
	Volume = 0;
	volumeFlag = 0;
	editMode_work = logoFadein;
}


void EditSelect::update(void)
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

	instance -> getSprite("floor") -> draw();
	instance -> getSprites("books") -> draw(anime_number);

	switch(editMode_work)
	{
	case logoFadein:
		logoFade();
		editSetUpDraw();
		break;
	case EditMenuSelect:
		editSetUpDraw();
		editSetUp();
		break;
	case Animation:
		animation();
		break;
	case Back:
		backAnimation();
		break;
	case Next:
		next();
		break;

	default:
		assert(!"•s³‚Èó‘Ô");
		break;
	}
}

void EditSelect::logoFade(void)
{
	if(size_section -> getAlpha() < 255)
	{
		size_section -> setAlpha(size_section -> getAlpha() + 5);
	}
	
	if(bg_section -> getAlpha() < 255)
	{
		bg_section -> setAlpha(bg_section -> getAlpha() + 5);
	}
	
	if(music_section -> getAlpha() < 255)
	{
		music_section -> setAlpha(music_section -> getAlpha() + 5);
	}

	if(instance -> getSprite("back")-> getAlpha() < 255)
	{
		instance -> getSprite("back") -> setAlpha(instance -> getSprite("back") -> getAlpha() + 5);
	}

	for(int i = 0; i <= 2; i++)
	{
		if(size_logo[i] -> getAlpha() < 255)
		{
			size_logo[i] -> setAlpha(size_logo[i] -> getAlpha() + 5);
		}

		if(bgm_logo[i] -> getAlpha() < 255)
		{
			bgm_logo[i] -> setAlpha(bgm_logo[i] -> getAlpha() + 5);
		}	
	}

	for(int i = 0; i < bgTextures.size(); i++)
	{
		if(bgTextures[i] -> getAlpha() < 255)
		{
			bgTextures[i] -> setAlpha(bgTextures[i] -> getAlpha() + 5);
		}
	}

	if(instance -> getSprite("frame") -> getAlpha() < 255)
	{
		instance -> getSprite("frame") -> setAlpha(instance -> getSprite("frame") -> getAlpha() + 5);
	}
	
	if(instance -> getSprite("frame") -> getAlpha() >= 255)
	{
		editMode_work = EditMenuSelect;
	}
}
	

void EditSelect::backAnimation(void)
{
	volumeFlag = 1;

	if (instance -> getSprites("books") -> getPositionX() < sWHeaf + 300)
	{
		instance -> getSprites("books") -> setPositionX(instance -> getSprites("books") -> getPositionX() + 10);
	}
	else
	{
		instance -> getSprites("books") -> setPositionX(sWHeaf + 300);
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
	}
}
	
void EditSelect::animation(void)
{
	if(bookAnmFlag == 0)
	{
		volumeFlag = 1;

		if(anime_number < BOOK_ANM_MAX)
		{
			anime_counter++;
			if(anime_counter % 7 == 0)
			{
				anime_counter = 0;
				anime_number++;
			}
		}
		else if(anime_number == BOOK_ANM_MAX)
		{
			bookAnmFlag = 1;
		}
	}
	else
	{
		anime_number = BOOK_ANM_MIN;
	}

	if (instance -> getSprites("books") -> getPositionX() < sWHeaf + 200)
	{
		instance -> getSprites("books") -> setPositionX(instance -> getSprites("books") -> getPositionX() + 10);
	}
	else
	{
		if(anime_number == BOOK_ANM_MIN)
		{
		instance -> getSprites("books") -> setPositionX(sWHeaf + 200);
		editMode_work = Next;
		}
	}
}


void EditSelect::editSetUp(void)
{
	switch(flag)
	{
	case StageSize:
		sizeSelect();
		break;
	case StageBG:
		bgSelect();
		break;
	case StageBGM:
		bgmSelect();
		break;
	default:
		assert(!"•s³‚Èó‘Ô");
		break;
	}
}

void EditSelect::sizeSelect(void)
{
	sizeCounter = CatGameLib::LibBasicFunc::wrap(sizeCounter, 0, 4);

	auto sizeSizeFunc = [&](void)
	{
		size_section -> setScale(0.8f);

		for(int i = 0; i <= 2; i++)
		{
			size_logo[i] -> setScale(0.25f);
		}
		
		instance -> getSprite("back") -> setScale(0.7f);
		instance -> getSprite("frame") -> setScale(0.15f);
	};

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		sizeCounter--;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		sizeCounter++;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(sizeCounter % 4 != 0)
		{
			size_section -> setScale(0.7f);
			flag = StageBG;
		}
		else
		{
			editMode_work = Back;
		}
	}

	if(flag == StageSize)
	{
		if(sizeCounter % 4 == 1)
		{
			sizeSizeFunc();
			size_logo[0] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_S);

			instance ->getSprite("frame") -> setPosition(sWHeaf - 100, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == 2)
		{
			sizeSizeFunc();
			size_logo[1] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_M);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 50, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == 3)
		{
			sizeSizeFunc();
			size_logo[2] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_L);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 200, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == 0)
		{
			sizeSizeFunc();
			size_section -> setScale(0.7f);

			instance -> getSprite("back") -> setScale(0.9f);
			instance ->getSprite("frame") ->setScaleX(0.3f);
			instance ->getSprite("frame") ->setScaleY(0.1f);
			instance ->getSprite("frame") -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}

void EditSelect::bgSelect(void)
{
	bgCounter = CatGameLib::LibBasicFunc::wrap(bgCounter, 0, 6);

	auto sizebgFunc = [&](void)
	{
		bg_section -> setScale(0.8f);
	
		instance -> getSprite("game_bg1") -> setScale(0.1f);
		instance -> getSprite("game_bg2") -> setScale(0.1f);
		instance -> getSprite("game_bg3") -> setScale(0.1f);
		instance -> getSprite("game_bg4") -> setScale(0.1f);
		instance -> getSprite("game_bg5") -> setScale(0.1f);
		
		instance -> getSprite("back") -> setScale(0.7f);
		instance -> getSprite("frame") -> setScale(0.2f);
	};

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		bgCounter--;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		bgCounter++;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(bgCounter % 6 != 0)
		{
			bg_section -> setScale(0.7f);
			flag = StageBGM;
		}
		else
		{
			editMode_work = Back;
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizebgFunc();
		bg_section -> setScale(0.7f);
		flag = StageSize;
	}

	if(flag == StageBG)
	{
		if(bgCounter % 6 == 1)
		{
			sizebgFunc();
			instance -> getSprite("game_bg1") -> setScale(0.2f);
			instance -> getSprite("game_bg1") -> draw();
			instance ->getSprite("frame") -> setPosition(sWHeaf - 100, sHHeaf - 30);

			stageConfig -> setBgNumber(StageConfig::BG_Castle);
		}
		else if(bgCounter % 6 == 2)
		{
			sizebgFunc();
			instance -> getSprite("game_bg2") -> setScale(0.2f);
			instance -> getSprite("game_bg2") -> draw();
			instance ->getSprite("frame") -> setPosition(sWHeaf - 25, sHHeaf - 30);

			stageConfig -> setBgNumber(StageConfig::BG_Table);
		}
		else if(bgCounter % 6 == 3)
		{
			sizebgFunc();
			instance -> getSprite("game_bg3") -> setScale(0.2f);
			instance -> getSprite("game_bg3") -> draw();
			instance ->getSprite("frame") -> setPosition(sWHeaf + 50, sHHeaf - 30);
			
			stageConfig -> setBgNumber(StageConfig::BG_Gate);
		}
		else if(bgCounter % 6 == 4)
		{
			sizebgFunc();
			instance -> getSprite("game_bg4") -> setScale(0.2f);
			instance -> getSprite("game_bg4") -> draw();
			instance ->getSprite("frame") -> setPosition(sWHeaf + 125, sHHeaf - 30);
			
			stageConfig -> setBgNumber(StageConfig::BG_Window);
		}
		else if(bgCounter % 6 == 5)
		{
			sizebgFunc();
			instance -> getSprite("game_bg5") -> setScale(0.2f);
			instance -> getSprite("game_bg5") -> draw();
			instance ->getSprite("frame") -> setPosition(sWHeaf + 200, sHHeaf - 30);
			
			stageConfig -> setBgNumber(StageConfig::BG_Throne);
		}
		else if(bgCounter % 6 == 0)
		{
			sizebgFunc();
			
			bg_section -> setScale(0.7f);

			instance -> getSprite("back") -> setScale(0.9f);
			instance ->getSprite("frame") ->setScaleX(0.3f);
			instance ->getSprite("frame") ->setScaleY(0.1f);
			instance ->getSprite("frame") -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}


void EditSelect::bgmSelect(void)
{
	bgmCounter = CatGameLib::LibBasicFunc::wrap(bgmCounter, 0, 4);

	auto sizeBgmFunc = [&](void)
	{
		music_section -> setScale(0.8f);

		for(int i = 0; i <= 2; i++)
		{
			bgm_logo[i] -> setScale(0.25f);
		}
		
		instance -> getSprite("back") -> setScale(0.7f);
		instance -> getSprite("frame") -> setScale(0.15f);
	};

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		bgmCounter--;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		bgmCounter++;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(bgmCounter % 4 != 0)
		{
			music_section -> setScale(0.7f);
			editMode_work = Animation;
		}
		else
		{
			editMode_work = Back;
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizeBgmFunc();
		music_section -> setScale(0.7f);
		flag = StageBG;
	}

	if(bgCounter % 6 == 1)
	{
		instance -> getSprite("game_bg1") -> draw();
	}
	else if(bgCounter % 6 == 2)
	{
		instance -> getSprite("game_bg2") -> draw();
	}
	else if(bgCounter % 6 == 3)
	{
		instance -> getSprite("game_bg3") -> draw();
	}
	else if(bgCounter % 6 == 4)
	{
		instance -> getSprite("game_bg4") -> draw();
	}
	else if(bgCounter % 6 == 5)
	{
		instance -> getSprite("game_bg5") -> draw();
	}
	
	if(flag == StageBGM)
	{
		if(bgmCounter % 4 == 1)
		{
			sizeBgmFunc();
			bgm_logo[0] -> setScale(0.35f);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf - 100, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_1);
		}
		else if(bgmCounter % 4 == 2)
		{
			sizeBgmFunc();
			bgm_logo[1] -> setScale(0.35f);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 50, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_2);
		}
		else if(bgmCounter % 4 == 3)
		{
			sizeBgmFunc();
			bgm_logo[2] -> setScale(0.35f);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 200, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_3);
		}
		else if(bgmCounter % 4 == 0)
		{
			sizeBgmFunc();
			music_section -> setScale(0.7f);

			instance -> getSprite("back") -> setScale(0.9f);
			instance ->getSprite("frame") ->setScaleX(0.3f);
			instance ->getSprite("frame") ->setScaleY(0.1f);
			instance ->getSprite("frame") -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}



void EditSelect::editSetUpDraw(void)
{
	size_section -> draw();
	bg_section -> draw();
	music_section -> draw();
	instance -> getSprite("back") -> draw();
	
	for(int i = 0; i <= 2; i++)
	{
		size_logo[i] -> draw();
		bgm_logo[i] -> draw();
	}

	for(int i = 0; i < bgTextures.size(); i++)
	{
		bgTextures[i] -> draw();
	}
	
	instance -> getSprite("frame") -> draw();
}


void EditSelect::fadeout(void)
{
}


void EditSelect::next(void)
{
	LibSound::allStop();
	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Edit);
}