
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "StageSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


StageSelect::StageSelect() : arrowRight(nullptr),
							 arrowLeft(nullptr)
{
	arrowRight = LibSprite::create("logo/arrow_right.png");
	arrowLeft = LibSprite::create("logo/arrow_left.png");
}


StageSelect::~StageSelect()
{
}


/**
 *	@brief 初期化
 *
 *	@author	Tatsuya Maeda
 */
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

	for(int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back(instance -> getSprite(bgName.c_str()));
	}

	volume = 0;
	volumeFlag = true;

	selectFlag = 0;
	counter = 0;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;

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

	arrowRight -> setPosition(sWHeaf + 150, sHHeaf - 310);
	arrowRight -> setScale(0.3f);
	arrowRight -> setAlpha(0.0f);

	arrowLeft -> setPosition(sWHeaf - 270, sHHeaf - 310);
	arrowLeft -> setScale(0.3f);
	arrowLeft -> setAlpha(0.0f);

	back -> setPosition(sWHeaf + 500, sHHeaf - 300);
	back -> setScale(1.0f);
	back -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 210, sHHeaf + 160);
	bgTextures[ResourceManager::BG_Castle] -> setScale(0.35f);
	bgTextures[ResourceManager::BG_Castle] -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf + 90, sHHeaf + 160);
	bgTextures[ResourceManager::BG_Table] -> setScale(0.3f);
	bgTextures[ResourceManager::BG_Table] -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf - 210, sHHeaf - 140);
	bgTextures[ResourceManager::BG_Gate] -> setScale(0.3f);
	bgTextures[ResourceManager::BG_Gate] -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 90, sHHeaf - 140);
	bgTextures[ResourceManager::BG_Window] -> setScale(0.3f);
	bgTextures[ResourceManager::BG_Window] -> setAlpha(0.0f);

	//ステージ選択から
	stageSelectWork = SelectStage;
}


/**
 *	@brief 更新
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::update(void)
{
	playSound();

	stageSelectDraw();

	switch(stageSelectWork)
	{
	case SelectStage:
		logoFadein();
		bgFadein();
		stageSelect();
		break;
	case BackAnimation:
		backAnimation();
		break;
	case Animation:
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


/**
 *	@brief 音声再生
 *
 *	@author	Tatsuya Maeda
 */
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


/**
 *	@brief 描画
 *
 *	@author	Tatsuya Maeda
 */
void  StageSelect::stageSelectDraw(void)
{
	floor -> draw();
	books -> draw(animeNumber);
	
	if(stageSelectWork == SelectStage)
	{
		for(int i = 0; i < ResourceManager::BG_Count - 1; i++)
		{
			bgTextures[i] -> draw();
		}

		arrowRight -> draw();
		arrowLeft -> draw();
		back -> draw();
		frame -> draw();
	}
}


/**
 *	@brief ロゴフェードイン
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::logoFadein(void)
{
	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + 5);
	}
	else
	{
		back -> setAlpha(255);
	}

	if(arrowRight -> getAlpha() < 255)
	{
		arrowRight -> setAlpha(arrowRight -> getAlpha() + 5);
	}
	else
	{
		arrowRight -> setAlpha(255);
	}

	if(arrowLeft -> getAlpha() < 255)
	{
		arrowLeft -> setAlpha(arrowLeft -> getAlpha() + 5);
	}
	else
	{
		arrowLeft -> setAlpha(255);
	}

	if(frame -> getAlpha() < 255)
	{
		frame -> setAlpha(frame -> getAlpha() + 5);
	}
	else
	{
		frame -> setAlpha(255);
	}
}


/**
 *	@brief ステージ背景フェードイン
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::bgFadein(void)
{
	for(int i = 0; i < ResourceManager::BG_Count - 1; i++)
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
}


/**
 *	@brief ステージ選択
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::stageSelect(void)
{
	cangeSize();

	if(frame -> getAlpha() == 255)
	{
		selectActions();
	}
}


/**
 *	@brief 選択操作
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::selectActions(void)
{
	const int counterNumber = CatGameLib::LibBasicFunc::wrap(counter, 0, 6);

	counter = CatGameLib::LibBasicFunc::wrap(counter, 0, 6);

	if(selectFlag != BackLogo)
	{
		selectFlag = counterNumber;

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
		{
			menuSelect -> play();
			counter -= 2;
		}

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			menuSelect -> play();
			counter += 2;
		}

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
		{
			menuSelect -> play();
			if(counterNumber % 2)
			{
				counter--;
			}
			else
			{
				selectFlag = BackLogo;
			}
		}

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
		{
			menuSelect -> play();
			if(counterNumber % 2)
			{
				selectFlag = BackLogo;
			}
			else
			{
				counter++;
			}
		}

		if (selectFlag != Leftarrow && selectFlag != Rightarrow && input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			fade -> setAlpha(0);
			stageSelectWork = Animation;
		}
	}
	else
	{
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
		{
			menuSelect -> play();
			if(counter % 2 == 0)
			{
				counter++;
				selectFlag = counter;
			}
			else
			{
				selectFlag = counter;
			}
		}
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
		{
			menuSelect -> play();
			if(counter % 2 == 0)
			{
				selectFlag = counter;
			}
			else
			{
				counter--;
				selectFlag = counter;
			}
		}

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
			animeNumber = BOOK_ANM_MAX;
			stageSelectWork = BackAnimation;
		}
	}
}


/**
 *	@brief ステージ背景、ロゴのサイズ変更
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::cangeSize(void)
{
	//全てのスケール設定
	auto sizeResetFunc = [&](void)
	{
		for(int i = 0; i < ResourceManager::BG_Count - 1; i++)
		{
			bgTextures[i] -> setScale(0.3f);
		}
		
		arrowLeft -> setScale(0.3f);
		arrowRight -> setScale(0.3f);
		back -> setScale(1.0f);
		frame -> setScale(0.35f);
	};


	switch(selectFlag)
	{
	case LeftUp:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Castle] -> setScale(0.35f);

		frame -> setPosition(bgTextures[ResourceManager::BG_Castle] -> getPosition());
		break;
	case RightUp:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Table] -> setScale(0.35f);

		frame -> setPosition(bgTextures[ResourceManager::BG_Table] -> getPosition());
		break;
	case LeftDown:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Gate] -> setScale(0.35f);

		frame -> setPosition(bgTextures[ResourceManager::BG_Gate] -> getPosition());
		break;
	case RightDown:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Window] -> setScale(0.35f);

		frame -> setPosition(bgTextures[ResourceManager::BG_Window] -> getPosition());
		break;
	case Leftarrow:
		sizeResetFunc();

		arrowLeft -> setScale(0.35f);

		frame -> setScale(0.1f);
		frame -> setPosition(arrowLeft -> getPosition());
		break;
	case Rightarrow:
		sizeResetFunc();

		arrowRight -> setScale(0.35f);

		frame -> setScale(0.1f);
		frame -> setPosition(arrowRight -> getPosition());
		break;
	case BackLogo:
		sizeResetFunc();

		back -> setScale(1.2f);

		frame -> setScaleX(0.35f);
		frame -> setScaleY(0.12f);
		frame -> setPosition(back -> getPosition());
		break;
	default:
		assert(!"不正な状態");
		break;
	}
}


/**
 *	@brief 本をめくる(1ページ戻す)アニメーション
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::backAnimation(void)
{
	volumeFlag = false;

	if(animeNumber > BOOK_ANM_MIN)
	{
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, 7);
		animeCounter++;
		if(animeCounter % 7 == 0)
		{
			animeCounter = 0;
			animeNumber--;
		}
	}
	else
	{
		animeNumber = BOOK_ANM_MIN;
		stageSelectWork = Next;		//次へ
	}
}


/**
 *	@brief 本をめくるアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::bookAnimation(void)
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
		animeNumber = BOOK_ANM_MAX;
	}
}


/**
 *	@brief フェードアウト
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::fadeout(void)
{
	if(fade -> getAlpha() < 255)
	{
		fade -> setAlpha(fade -> getAlpha() + 5);
	}
	else
	{
		fade -> setAlpha(255);
		stageSelectWork = Next;		//次へ
	}
}


/**
 *	@brief selectFlagがBackLogoならメニューセレクトへ、それ以外はゲームへ
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::next(void)
{
	LibSound::allStop();

	if(selectFlag != BackLogo)
	{
		//ゲームへ
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
	}
	else
	{
		//メニューセレクトへ
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
	}

}
