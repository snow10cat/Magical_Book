
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


EditSelect::EditSelect() : sizeSection(nullptr),
						   bgSection(nullptr),
						   musicSection(nullptr)
{
	sizeSection = CatGameLib::LibSprite::create("logo/size_section.png");
	bgSection = CatGameLib::LibSprite::create("logo/bg_section.png");
	musicSection = CatGameLib::LibSprite::create("logo/music_section.png");

	bgmLogos[ResourceManager::BGM_1] = CatGameLib::LibSprite::create("logo/bgm1.png");
	bgmLogos[ResourceManager::BGM_2] = CatGameLib::LibSprite::create("logo/bgm2.png");
	bgmLogos[ResourceManager::BGM_3] = CatGameLib::LibSprite::create("logo/bgm3.png");;

	sizeLogo[ResourceManager::Size_S] = CatGameLib::LibSprite::create("logo/S.png");
	sizeLogo[ResourceManager::Size_M] = CatGameLib::LibSprite::create("logo/M.png");
	sizeLogo[ResourceManager::Size_L] = CatGameLib::LibSprite::create("logo/L.png");
}


EditSelect::~EditSelect()
{
}


/**
 *	@brief 初期化
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::init(void)
{
	input = LibInput::getInstance();

	selectBgm = instance -> getSound("selectbgm");
	menuSelect = instance -> getSound("menuSelect");

	floor = instance ->getSprite("floor");
	books = instance -> getSprites("books");
	frame = instance -> getSprite("frame");
	back = instance -> getSprite("back");

	for(int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back(instance -> getSprite(bgName.c_str()));
	}

	volume = 0;
	volumeFlag = true;

	sizeCounter = 1;
	bgCounter = 1;
	bgmCounter = 1;
	flag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;

	//音声
	selectBgm -> setVolume(0.0f);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(1.0f);

	//画像
	books -> setPosition(sWHeaf - 320, sHHeaf);
	books -> setScale(1.5f);

	for(int i = 0; i <= ResourceManager::Size_Count - 1; i++)
	{
		sizeLogo[i] -> setAlpha(0.0f);
	}

	//!< 大きさ
	sizeSection -> setPosition(sWHeaf - 100, sHHeaf + 300);
	sizeSection -> setScale(0.8f);
	sizeSection -> setAlpha(0.0f);

	sizeLogo[ResourceManager::Size_S] -> setPosition(sWHeaf - 100, sHHeaf + 200);
	sizeLogo[ResourceManager::Size_S] -> setScale(0.35f);

	sizeLogo[ResourceManager::Size_M] -> setPosition(sWHeaf + 50, sHHeaf + 200);
	sizeLogo[ResourceManager::Size_M] -> setScale(0.25f);

	sizeLogo[ResourceManager::Size_L] -> setPosition(sWHeaf + 200, sHHeaf + 200);
	sizeLogo[ResourceManager::Size_L] -> setScale(0.25f);

	//!< 背景
	bgSection -> setPosition(sWHeaf - 100, sHHeaf + 80);
	bgSection -> setScale(0.7f);
	bgSection -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 100, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf - 25, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf + 50, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 125, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Throne] -> setPosition(sWHeaf + 200, sHHeaf - 30);
	
	for(int i = 0; i <= ResourceManager::BG_Count - 1; i++)
	{
		bgTextures[i] -> setScale(0.1f);
		bgTextures[i] -> setAlpha(0.0f);
	}

	//!< 音楽
	musicSection -> setPosition(sWHeaf - 100, sHHeaf - 140);
	musicSection -> setScale(0.7f);
	musicSection -> setAlpha(0.0f);
	
	bgmLogos[ResourceManager::BGM_1] -> setPosition(sWHeaf - 100, sHHeaf - 220);

	bgmLogos[ResourceManager::BGM_2] -> setPosition(sWHeaf + 50, sHHeaf - 220);

	bgmLogos[ResourceManager::BGM_3] -> setPosition(sWHeaf + 200, sHHeaf - 220);
	
	for(int i = 0; i <= ResourceManager::BGM_Count - 1; i++)
	{
		bgmLogos[i] -> setScale(0.25f);
		bgmLogos[i] -> setAlpha(0.0f);
	}

	frame -> setPosition(sWHeaf - 100, sHHeaf + 200);
	frame -> setScale(0.15f);
	frame -> setAlpha(0.0f);

	back -> setPosition(sWHeaf - 500, sHHeaf - 280);
	back -> setScale(0.7f);
	back -> setAlpha(0.0f);

	//フェードインから
	editSetWork = Fadein;
}


/**
 *	@brief 更新
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::update(void)
{
	playSound();

	editSetUpDraw();

	switch(editSetWork)
	{
	case Fadein:
		logoFadein();
		break;
	case EditMenuSelect:
		editSetUp();
		break;
	case BackAnimation:
		backAnimation();
		break;
	case Animation:
		bookAnimation();
		break;
	case Next:
		next();
		break;
	default:
		assert(!"不正な状態");
		break;
	}
}


/**
 *	@brief 音声再生
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::playSound(void)
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


/**
 *	@brief 描画
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::editSetUpDraw(void)
{
	floor -> draw();
	books -> draw(anime_number);

	if(editSetWork == Fadein || editSetWork == EditMenuSelect)
	{
		sizeSection -> draw();

		for(int i = 0; i < ResourceManager::Size_Count; i++)
		{
			sizeLogo[i] -> draw();
		}

		bgSection -> draw();

		for(int i = 0; i < ResourceManager::BG_Count; i++)
		{
			bgTextures[i] -> draw();
		}

		musicSection -> draw();
		
		for(int i = 0; i < ResourceManager::BGM_Count; i++)
		{
			bgmLogos[i] -> draw();
		}

		back -> draw();
		frame -> draw();
	}
}


/**
 *	@brief ロゴフェードイン
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::logoFadein(void)
{
	if(sizeSection -> getAlpha() < 255)
	{
		sizeSection -> setAlpha(sizeSection -> getAlpha() + 5);
	}
	else
	{
		sizeSection -> setAlpha(255);
	}

	for(int i = 0; i < ResourceManager::Size_Count; i++)
	{
		if(sizeLogo[i] -> getAlpha() < 255)
		{
			sizeLogo[i] -> setAlpha(sizeLogo[i] -> getAlpha() + 5);
		}
		else
		{
			sizeLogo[i] -> setAlpha(255);
		}
	}

	if(bgSection -> getAlpha() < 255)
	{
		bgSection -> setAlpha(bgSection -> getAlpha() + 5);
	}
	else
	{
		bgSection -> setAlpha(255);
	}

	for(int i = 0; i < ResourceManager::BG_Count; i++)
	{
		if(bgTextures[i] -> getAlpha() < 255)
		{
			bgTextures[i] -> setAlpha(bgTextures[i] -> getAlpha() + 5);
		}
		else
		{
			bgTextures[i] -> setAlpha(255);
		}
	}

	if(musicSection -> getAlpha() < 255)
	{
		musicSection -> setAlpha(musicSection -> getAlpha() + 5);
	}
	else
	{
		musicSection -> setAlpha(255);
	}
	for(int i = 0; i < ResourceManager::BGM_Count; i++)
	{
		if(bgmLogos[i] -> getAlpha() < 255)
		{
			bgmLogos[i] -> setAlpha(bgmLogos[i] -> getAlpha() + 5);
		}
		else
		{
			bgmLogos[i] -> setAlpha(255);
		}
	}

	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + 5);
	}
	else
	{
		back -> setAlpha(255);
	}

	if(frame -> getAlpha() < 255)
	{
		frame -> setAlpha(frame -> getAlpha() + 5);
	}
	else
	{
		frame -> setAlpha(255);
		editSetWork = EditMenuSelect;
	}
}


/**
 *	@brief 設定画面
 *
 *	@author	Tatsuya Maeda
 */
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
		assert(!"不正な状態");
		break;
	}
}


/**
 *	@brief サイズ選択
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::sizeSelect(void)
{
	sizeCounter = CatGameLib::LibBasicFunc::wrap(sizeCounter, 0, 4);

	auto sizeSizeFunc = [&](void)
	{
		sizeSection -> setScale(0.8f);

		for(int i = 0; i <= 2; i++)
		{
			sizeLogo[i] -> setScale(0.25f);
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
			sizeSection -> setScale(0.7f);
			flag = StageBG;
		}
		else
		{
			editSetWork = BackAnimation;
		}
	}

	if(flag == StageSize)
	{
		if(sizeCounter % 4 == 1)
		{
			sizeSizeFunc();
			sizeLogo[0] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_S);

			instance ->getSprite("frame") -> setPosition(sWHeaf - 100, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == 2)
		{
			sizeSizeFunc();
			sizeLogo[1] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_M);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 50, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == 3)
		{
			sizeSizeFunc();
			sizeLogo[2] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_L);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 200, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == 0)
		{
			sizeSizeFunc();
			sizeSection -> setScale(0.7f);

			instance -> getSprite("back") -> setScale(0.9f);
			instance ->getSprite("frame") ->setScaleX(0.3f);
			instance ->getSprite("frame") ->setScaleY(0.1f);
			instance ->getSprite("frame") -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}


/**
 *	@brief 背景選択
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bgSelect(void)
{
	bgCounter = CatGameLib::LibBasicFunc::wrap(bgCounter, 0, 6);

	auto sizebgFunc = [&](void)
	{
		bgSection -> setScale(0.8f);
	
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
			bgSection -> setScale(0.7f);
			flag = StageBGM;
		}
		else
		{
			editSetWork = BackAnimation;
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizebgFunc();
		bgSection -> setScale(0.7f);
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
			
			bgSection -> setScale(0.7f);

			instance -> getSprite("back") -> setScale(0.9f);
			instance ->getSprite("frame") ->setScaleX(0.3f);
			instance ->getSprite("frame") ->setScaleY(0.1f);
			instance ->getSprite("frame") -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}


/**
 *	@brief 音楽選択
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bgmSelect(void)
{
	bgmCounter = CatGameLib::LibBasicFunc::wrap(bgmCounter, 0, 4);

	auto sizeBgmFunc = [&](void)
	{
		musicSection -> setScale(0.8f);

		for(int i = 0; i <= 2; i++)
		{
			bgmLogos[i] -> setScale(0.25f);
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
			musicSection -> setScale(0.7f);
			editSetWork = Animation;
		}
		else
		{
			editSetWork = BackAnimation;
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizeBgmFunc();
		musicSection -> setScale(0.7f);
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
			bgmLogos[0] -> setScale(0.35f);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf - 100, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_1);
		}
		else if(bgmCounter % 4 == 2)
		{
			sizeBgmFunc();
			bgmLogos[1] -> setScale(0.35f);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 50, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_2);
		}
		else if(bgmCounter % 4 == 3)
		{
			sizeBgmFunc();
			bgmLogos[2] -> setScale(0.35f);
			
			instance ->getSprite("frame") -> setPosition(sWHeaf + 200, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_3);
		}
		else if(bgmCounter % 4 == 0)
		{
			sizeBgmFunc();
			musicSection -> setScale(0.7f);

			instance -> getSprite("back") -> setScale(0.9f);
			instance ->getSprite("frame") ->setScaleX(0.3f);
			instance ->getSprite("frame") ->setScaleY(0.1f);
			instance ->getSprite("frame") -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}


/**
 *	@brief 本をめくる(1ページ戻す)アニメーション
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::backAnimation(void)
{
	volumeFlag = false;

	if (books -> getPositionX() < sWHeaf + 300)
	{
		books -> setPositionX(books -> getPositionX() + 10);
	}
	else
	{
		instance -> getSprites("books") -> setPositionX(sWHeaf + 300);
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
	}
}


/**
 *	@brief 本をめくるアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bookAnimation(void)
{
	if(bookAnmFlag == 0)
	{
		volumeFlag = false;

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
		editSetWork = Next;
		}
	}
}


/**
 *	@brief エディットへ
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::next(void)
{
	LibSound::allStop();
	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Edit);
}