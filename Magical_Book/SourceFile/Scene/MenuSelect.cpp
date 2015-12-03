
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "MenuSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


MenuSelect::MenuSelect() : selectBgm(nullptr),
						   play(nullptr),
						   make(nullptr)
{
	
	selectBgm = LibSound::create("bgm/menuselect.wav");
	play = LibSprite::create("logo/play.png");
	make = LibSprite::create("logo/make.png");
}


MenuSelect::~MenuSelect()
{
}


/**
 *	@brief 初期化
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::init(void)
{
	input = LibInput::getInstance();
	
	menuSelect = instance -> getSound("menuSelect");

	fade = instance ->getSprite("fade");
	floor = instance -> getSprite("floor");
	openBooks = instance -> getSprites("openBook");
	books = instance -> getSprites("books");
	back = instance -> getSprite("back");

	volume = 0;
	volumeFlag = true;

	timer = 0;
	counter = 0;
	flag = true;
	fadeFlag = true;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;
	size = 1.3;

	//音声
	selectBgm -> setVolume(volume);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(1.0f);

	//画像
	if(SceneManager::getInstance() -> getOldSceneNumber() == SceneManager::SceneNumber::Title)
	{
		fade -> setAlpha(255);
	}
	else
	{
		fade -> setAlpha(0);
	}

	books -> setPosition(sWHeaf + 300, sHHeaf);
	books -> setScale(1.5f);

	openBooks -> setPosition(sWHeaf + 300, sHHeaf);
	openBooks -> setScale(1.5f);

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(1.3f);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(1.0f);
	make -> setAlpha(0.0f);

	back -> setPosition(sWHeaf - 100, sHHeaf - 200);
	back -> setScale(1.0f);
	back -> setAlpha(0.0f);

	//フェードインから
	selectWork = Fadein;
}


/**
 *	@brief 更新
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::update(void)
{
	playSound();

	menuSelectDraw();

	switch(selectWork)
	{
	case Fadein:
		if(SceneManager::getInstance() -> getOldSceneNumber() == SceneManager::SceneNumber::Title)
		{
			fadein();
			logoFadein();
		}
		else
		{
			logoFadein();
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
		assert(!"不正な状態");
		break;
	}
}


/**
 *	@brief 音声再生
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::playSound(void)
{
	if(selectBgm -> getState() != LibSound::Play)
	{
		selectBgm -> play();
	}

	if(volumeFlag == false)
	{
		//BGMフェードアウト
		volume -= 0.02f;
		selectBgm -> setVolume(volume);
	}
	else if(volume <= 1.0 && volumeFlag == true)
	{
		//BGMフェードイン
		volume += 0.02f;
		selectBgm -> setVolume(volume);
	}
}


/**
 *	@brief 描画
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::menuSelectDraw(void)
{
	floor -> draw();

	if(selectWork == Animation && counter == 2)
	{
		openBooks -> draw(animeNumber);
	}
	else
	{
		books -> draw(animeNumber);
	}

	if(selectWork == Fadein || selectWork == ModeSelect)
	{
		play -> draw();
		make -> draw();
		back -> draw();
	}

	fade -> draw();
}


/**
 *	@brief フェードイン
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::fadein(void)
{
	if(fade -> getAlpha() > 0)
	{
		fade -> setAlpha(fade -> getAlpha() - 5);
	}
	else
	{
		fade -> setAlpha(0);
	}
}


/**
 *	@brief ロゴフェードイン
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::logoFadein(void)
{
	if(play-> getAlpha() < 255)
	{
		play -> setAlpha(play -> getAlpha() + 5);
	}
	else
	{
		play -> setAlpha(255);
	}

	if(make-> getAlpha() < 255)
	{
		make -> setAlpha(make -> getAlpha() + 5);
	}
	else
	{
		make -> setAlpha(255);
	}

	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + 5);
	}
	else
	{
		back -> setAlpha(255);
		
		selectWork = ModeSelect;
	}
}


/**
 *	@brief モード選択
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::modeSelect(void)
{
	counter = CatGameLib::LibBasicFunc::wrap(counter, 0, 3);

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
	{
		timer = 0;
		counter--;
		flag = true;
		size = 1.3;
		menuSelect -> play();
	}
	else if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		timer = 0;
		counter++;
		flag = true;
		size = 1.3;
		menuSelect -> play();
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
			flag = true;
			play -> setAlpha(0.0f);
			make -> setAlpha(0.0f);
			back -> setAlpha(0.0f);
			selectWork = Animation;		//アニメーションへ
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
			flag = true;
			play -> setAlpha(0.0f);
			make -> setAlpha(0.0f);
			back -> setAlpha(0.0f);
			selectWork = Animation;		//アニメーションへ
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
			animeNumber = BOOK_ANM_MAX;
			size = 1.5f;
			selectWork = Animation;		//アニメーションへ
		}
	}
}


/**
 *	@brief ロゴアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::logoAnimation(void)
{
	timer = CatGameLib::LibBasicFunc::wrap(timer, 0, 3);

	timer++;

	if(timer % 3 == 0)
	{
		if(size <= 1.5 && flag == true)
		{
			if(size >= 1.4)
			{
				flag = false;
			}
			
			size += 0.01f;
		}
		else if(size >= 1.1 && flag == false)
		{
			if(size <= 1.2)
			{	
				flag = true;
			}
			
			size -= 0.01;
		}
	}
}


/**
 *	@brief 移行アニメーション
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::animation(void)
{	
	volumeFlag = false;

	if(counter == 0)
	{
		bookAnimation();

		if(animeNumber == BOOK_ANM_MAX)
		{
			animeNumber = BOOK_ANM_MIN;
			animeCounter = 0;
			selectWork = Next;		//ステージ選択へ
		}
	}
	else if(counter == 1)
	{
		//本の移動
		if (books -> getPositionX() > sWHeaf - 320)
		{
			books -> setPositionX(books -> getPositionX() - 10);
		}
		else
		{
			books -> setPositionX(sWHeaf - 320);
			selectWork = Next;		//エディット選択へ
		}
	}
	else
	{
		openBooks -> setScale(size);

		//本の移動
		if (openBooks -> getPositionX() > sWHeaf - 250)
		{
			openBooks -> setPositionX(openBooks -> getPositionX() - 10);
		}
		else
		{
			openBooks -> setPositionX(sWHeaf - 250);
		}

		if(animeNumber > BOOK_ANM_MIN)
		{
			closeAnimation();
		}

		if(size == 1.0 && animeNumber == BOOK_ANM_MIN && openBooks -> getPositionX() == sWHeaf - 250)
		{
			if(fade -> getAlpha() < 255 && fadeFlag == true)
			{
				fadeout();
				if(fade -> getAlpha() == 255)
				{
					fadeFlag = false;
				}
			}
			else if(fade -> getAlpha() > 0 && fadeFlag == false)
			{
				fadein();
			}

			if(fade -> getAlpha() <= 0)
			{
				selectWork = Next;		//タイトルへ
			}
		}
	}
}


/**
 *	@brief 本をめくるアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::bookAnimation(void)
{
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
 *	@brief 本を閉じるアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::closeAnimation(void)
{
	if(animeNumber > BOOK_ANM_MIN)
	{
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, 7);
		animeCounter++;
		if(animeCounter % 7 == 0)
		{
			animeCounter = 0;
			animeNumber--;
			
			if(size > 1)
			{
				size -= 0.1f;
			}
			else if(size <= 1)
			{
				size = 1.0f;
			}
		}
	}
	else
	{
		animeNumber = BOOK_ANM_MIN;
	}
}


/**
 *	@brief フェードアウト
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::fadeout(void)
{
	if(fade -> getAlpha() < 255)
	{
		fade -> setAlpha(fade -> getAlpha() + 5);
	}
	else
	{
		fade -> setAlpha(255);
	}
}


/**
 *	@brief counterが0ならステージセレクト、1ならエディットセレクトへ、それ以外はタイトルへ
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::next(void)
{
	LibSound::allStop();		//すべてのサウンド停止
	if(counter == 0)
	{
		//ステージセレクトへ
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::StageSelect);
	}
	else if(counter == 1)
	{
		//エディットセレクトへ
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}
	else
	{
		//タイトルへ
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Title);
	}
}