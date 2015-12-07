
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

	sizeCounter = EditSize::Size_S;
	bgCounter = EditBg::BG_Castle;
	bgmCounter = EditBgm::Bgm_1;
	flag = 0;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;

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

	//大きさ
	sizeSection -> setPosition(sWHeaf - 100, sHHeaf + 300);
	sizeSection -> setScale(0.8f);
	sizeSection -> setAlpha(0.0f);

	sizeLogo[ResourceManager::Size_S] -> setPosition(sWHeaf - 100, sHHeaf + 200);
	sizeLogo[ResourceManager::Size_S] -> setScale(0.35f);

	sizeLogo[ResourceManager::Size_M] -> setPosition(sWHeaf + 50, sHHeaf + 200);
	sizeLogo[ResourceManager::Size_M] -> setScale(0.25f);

	sizeLogo[ResourceManager::Size_L] -> setPosition(sWHeaf + 200, sHHeaf + 200);
	sizeLogo[ResourceManager::Size_L] -> setScale(0.25f);

	//背景
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
	books -> draw(animeNumber);

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
		editSetWork = EditMenuSelect;		//選択画面へ
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

	//全てのスケール設定
	auto sizeSizeFunc = [&](void)
	{
		sizeSection -> setScale(0.8f);

		for(int i = 0; i < ResourceManager::Size_Count; i++)
		{
			sizeLogo[i] -> setScale(0.25f);
		}
		
		back -> setScale(0.7f);
		frame -> setScale(0.15f);
	};

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		menuSelect -> play();
		sizeCounter--;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		menuSelect -> play();
		sizeCounter++;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(sizeCounter % 4 != BACK)
		{
			sizeSection -> setScale(0.7f);
			flag = StageBG;		//背景選択へ
		}
		else
		{
			editSetWork = BackAnimation;		//戻るアニメーションへ
		}
	}

	if(flag == StageSize)
	{
		if(sizeCounter % 4 == Size_S)
		{
			sizeSizeFunc();
			sizeLogo[ResourceManager::Size_S] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_S);

			frame -> setPosition(sWHeaf - 100, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == Size_M)
		{
			sizeSizeFunc();
			sizeLogo[ResourceManager::Size_M] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_M);
			
			frame -> setPosition(sWHeaf + 50, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == Size_L)
		{
			sizeSizeFunc();
			sizeLogo[ResourceManager::Size_L] -> setScale(0.35f);
			stageConfig -> setSizeNumber(StageConfig::Size_L);
			
			frame -> setPosition(sWHeaf + 200, sHHeaf + 200);
		}
		else if(sizeCounter % 4 == BACK)
		{
			sizeSizeFunc();
			sizeSection -> setScale(0.7f);

			back -> setScale(0.9f);
			frame ->setScaleX(0.3f);
			frame ->setScaleY(0.1f);
			frame -> setPosition(sWHeaf - 500, sHHeaf - 280);
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
	
	//全てのスケール設定
	auto sizebgFunc = [&](void)
	{
		bgSection -> setScale(0.8f);
	
		for(int i = 0; i < ResourceManager::BG_Count; i++)
		{
			bgTextures[i] -> setScale(0.1f);
		}

		back -> setScale(0.7f);
		frame -> setScale(0.2f);
	};

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		menuSelect -> play();
		bgCounter--;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		menuSelect -> play();
		bgCounter++;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(bgCounter % 6 != BACK)
		{
			bgSection -> setScale(0.7f);
			flag = StageBGM;		//BGM選択へ
		}
		else
		{
			editSetWork = BackAnimation;		//戻るアニメーションへ
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizebgFunc();
		bgSection -> setScale(0.7f);
		flag = StageSize;		//サイズ選択へ
	}

	if(flag == StageBG)
	{
		if(bgCounter % 6 == BG_Castle)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Castle] -> setScale(0.2f);
			bgTextures[ResourceManager::BG_Castle] -> draw();
			frame -> setPosition(sWHeaf - 100, sHHeaf - 30);

			stageConfig -> setBgNumber(StageConfig::BG_Castle);
		}
		else if(bgCounter % 6 == BG_Table)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Table] -> setScale(0.2f);
			bgTextures[ResourceManager::BG_Table] -> draw();
			frame -> setPosition(sWHeaf - 25, sHHeaf - 30);

			stageConfig -> setBgNumber(StageConfig::BG_Table);
		}
		else if(bgCounter % 6 == BG_Gate)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Gate] -> setScale(0.2f);
			bgTextures[ResourceManager::BG_Gate] -> draw();
			frame -> setPosition(sWHeaf + 50, sHHeaf - 30);
			
			stageConfig -> setBgNumber(StageConfig::BG_Gate);
		}
		else if(bgCounter % 6 == BG_Window)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Window] -> setScale(0.2f);
			bgTextures[ResourceManager::BG_Window] -> draw();
			frame -> setPosition(sWHeaf + 125, sHHeaf - 30);
			
			stageConfig -> setBgNumber(StageConfig::BG_Window);
		}
		else if(bgCounter % 6 == BG_Throne)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Throne] -> setScale(0.2f);
			bgTextures[ResourceManager::BG_Throne] -> draw();
			frame -> setPosition(sWHeaf + 200, sHHeaf - 30);
			
			stageConfig -> setBgNumber(StageConfig::BG_Throne);
		}
		else if(bgCounter % 6 == BACK)
		{
			sizebgFunc();
			
			bgSection -> setScale(0.7f);

			back -> setScale(0.9f);
			frame ->setScaleX(0.3f);
			frame ->setScaleY(0.1f);
			frame -> setPosition(sWHeaf - 500, sHHeaf - 280);
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
	
	//全てのスケール設定
	auto sizeBgmFunc = [&](void)
	{
		musicSection -> setScale(0.8f);

		for(int i = 0; i <= 2; i++)
		{
			bgmLogos[i] -> setScale(0.25f);
		}
		
		back -> setScale(0.7f);
		frame -> setScale(0.15f);
	};

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		menuSelect -> play();
		bgmCounter--;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		menuSelect -> play();
		bgmCounter++;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(bgmCounter % 4 !=BACK)
		{
			musicSection -> setScale(0.7f);
			editSetWork = Animation;		//アニメーションへ
		}
		else
		{
			editSetWork = BackAnimation;	//戻るアニメーションへ
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizeBgmFunc();
		musicSection -> setScale(0.7f);
		flag = StageBG;		//背景選択へ
	}

	if(bgCounter % 6 == BG_Castle)
	{
		bgTextures[ResourceManager::BG_Castle] -> draw();
	}
	else if(bgCounter % 6 == BG_Table)
	{
		bgTextures[ResourceManager::BG_Table] -> draw();
	}
	else if(bgCounter % 6 == BG_Gate)
	{
		bgTextures[ResourceManager::BG_Gate] -> draw();
	}
	else if(bgCounter % 6 == BG_Window)
	{
		bgTextures[ResourceManager::BG_Window] -> draw();
	}
	else if(bgCounter % 6 == BG_Throne)
	{
		bgTextures[ResourceManager::BG_Throne] -> draw();
	}
	
	if(flag == StageBGM)
	{
		if(bgmCounter % 4 == Bgm_1)
		{
			sizeBgmFunc();
			bgmLogos[ResourceManager::BGM_1] -> setScale(0.35f);
			
			frame -> setPosition(sWHeaf - 100, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_1);
		}
		else if(bgmCounter % 4 == 2)
		{
			sizeBgmFunc();
			bgmLogos[ResourceManager::BGM_2] -> setScale(0.35f);
			
			frame -> setPosition(sWHeaf + 50, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_2);
		}
		else if(bgmCounter % 4 == 3)
		{
			sizeBgmFunc();
			bgmLogos[ResourceManager::BGM_3] -> setScale(0.35f);
			
			frame -> setPosition(sWHeaf + 200, sHHeaf - 220);
			
			stageConfig -> setMusicNumber(StageConfig::BGM_3);
		}
		else if(bgmCounter % 4 == BACK)
		{
			sizeBgmFunc();
			musicSection -> setScale(0.7f);

			back -> setScale(0.9f);
			frame ->setScaleX(0.3f);
			frame ->setScaleY(0.1f);
			frame -> setPosition(sWHeaf - 500, sHHeaf - 280);
		}
	}
}


/**
 *	@brief 本を移動させるアニメーション
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
		books -> setPositionX(sWHeaf + 300);
		editSetWork = Next;
	}
}


/**
 *	@brief 本をめくるアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bookAnimation(void)
{
	volumeFlag = false;

	if(animeNumber < BOOK_ANM_MAX)
	{
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, 7);
		animeCounter++;
		if(animeCounter % 7 == 0)
		{
			animeCounter = 0;
			animeNumber++;
		}
	}
	else
	{
		animeNumber = BOOK_ANM_MIN;
	}

	if (books -> getPositionX() < sWHeaf + 200)
	{
		books -> setPositionX(books -> getPositionX() + 10);
	}
	else
	{
		if(animeNumber == BOOK_ANM_MIN)
		{
			books -> setPositionX(sWHeaf + 200);
			editSetWork = Next;		//エディット画面へ
		}
	}
}


/**
 *	@brief flagがBACKならメニューセレクトへ、それ以外ならエディットへ
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::next(void)
{
	LibSound::allStop();

	if(sizeCounter == BACK || bgCounter == BACK || bgmCounter == BACK)
	{
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
	}
	else
	{
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Edit);
	}
}