
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "MenuSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


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
	
	menuSelect = ResourceManager::getInstance() -> getSound("menuSelect");

	fade = ResourceManager::getInstance() ->getSprite("fade");
	floor = ResourceManager::getInstance() -> getSprite("floor");
	openBooks = ResourceManager::getInstance() -> getSprites("openBook");
	books = ResourceManager::getInstance() -> getSprites("books");
	back = ResourceManager::getInstance() -> getSprite("back");

	volume = 0;
	volumeFlag = true;

	timer = 0;
	logoFlag = 1;
	counter = 0;
	flag = true;
	fadeFlag = true;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;
	size = DEFAULT_SIZE;
	bookSize = BOOK_SIZE;

	//音声
	selectBgm -> setVolume(volume);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(MAX_VOLUME);

	//画像
	if(SceneManager::getInstance() -> getOldSceneNumber() == SceneManager::SceneNumber::Title)
	{
		fade -> setAlpha(255);
	}
	else
	{
		fade -> setAlpha(0);
	}

	books -> setPosition(sWHeaf + BOOK_POS_X, sHHeaf);
	books -> setScale(BOOK_SIZE);

	openBooks -> setPosition(sWHeaf + BOOK_POS_X, sHHeaf);
	openBooks -> setScale(BOOK_SIZE);

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(DEFAULT_SIZE);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(DEFAULT_SIZE);
	make -> setAlpha(0.0f);

	back -> setPosition(sWHeaf - 100, sHHeaf - 200);
	back -> setScale(DEFAULT_SIZE);
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
	case BackAnimation:
		backAnimation();
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
		volume -= BGM_FADE;
	}
	else if(volume <= MAX_VOLUME && volumeFlag == true)
	{
		//BGMフェードイン
		volume += BGM_FADE;
	}
	selectBgm -> setVolume(volume);
}


/**
 *	@brief 描画
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::menuSelectDraw(void)
{
	floor -> draw();

	if(selectWork == BackAnimation)
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
		fade -> setAlpha(fade -> getAlpha() - FADE);
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
		play -> setAlpha(play -> getAlpha() + FADE);
	}
	else
	{
		play -> setAlpha(255);
	}

	if(make-> getAlpha() < 255)
	{
		make -> setAlpha(make -> getAlpha() + FADE);
	}
	else
	{
		make -> setAlpha(255);
	}

	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + FADE);
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
		menuSelect -> play();
		timer = 0;
		counter--;
		logoFlag = 1;
		size = DEFAULT_SIZE;
	}
	else if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		menuSelect -> play();
		timer = 0;
		counter++;
		logoFlag = 1;
		size = DEFAULT_SIZE;
	}

	if (counter % 3 == 0)
	{
		//ステージ選択へ
		play -> setScale(size);
		make -> setScale(DEFAULT_SIZE);
		back -> setScale(DEFAULT_SIZE);

		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			timer = 0;
			flag = true;
			selectWork = Animation;		//アニメーションへ
		}
	}
	else if (counter % 3 == 1)
	{
		//ゲームエディットへ
		play -> setScale(DEFAULT_SIZE);
		make -> setScale(size);
		back -> setScale(DEFAULT_SIZE);

		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			timer = 0;
			flag = true;
			selectWork = Animation;		//アニメーションへ
		}
	}
	else
	{
		//タイトルへ
		play -> setScale(DEFAULT_SIZE);
		make -> setScale(DEFAULT_SIZE);
		back -> setScale(size);

		logoAnimation();

		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			animeNumber = BOOK_ANM_MAX;
			bookSize = BOOK_SIZE;
			selectWork = BackAnimation;		//アニメーションへ
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
	timer = CatGameLib::LibBasicFunc::wrap(timer, 0, LOGO_ANIM_SPEED);

	timer++;

	if(timer % LOGO_ANIM_SPEED == 0)
	{
		if(size >= LOGO_MAX_SIZE || size <= LOGO_MIN_SIZE)
		{
			logoFlag *= -1;
		}

		size += LOGO_SIZE_ADD * logoFlag;
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
		if (books -> getPositionX() > sWHeaf - EDIT_SEL_BOOK_POS_X)
		{
			books -> setPositionX(books -> getPositionX() - MOVEMENT_BOOK);
		}
		else
		{
			books -> setPositionX(sWHeaf - EDIT_SEL_BOOK_POS_X);
			selectWork = Next;		//エディット選択へ
		}
	}
}


/**
 *	@brief 戻る移行アニメーション
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::backAnimation()
{
	openBooks -> setScale(bookSize);

	//本の移動
	if (openBooks -> getPositionX() > sWHeaf - TITLE_BOOK_POS_X)
	{
		openBooks -> setPositionX(openBooks -> getPositionX() - FADE);
	}
	else
	{
		openBooks -> setPositionX(sWHeaf - TITLE_BOOK_POS_X);
	}

	if(animeNumber > BOOK_ANM_MIN)
	{
		closeAnimation();
	}

	if(bookSize == DEFAULT_SIZE && animeNumber == BOOK_ANM_MIN && openBooks -> getPositionX() == sWHeaf - TITLE_BOOK_POS_X)
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


/**
 *	@brief 本をめくるアニメーション
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::bookAnimation(void)
{
	if(animeNumber < BOOK_ANM_MAX)
	{
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, BOOK_ANIM_SPEED);
		animeCounter++;
		if(animeCounter % BOOK_ANIM_SPEED == 0)
		{
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
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, BOOK_ANIM_SPEED);
		animeCounter++;
		if(animeCounter % BOOK_ANIM_SPEED == 0)
		{
			animeNumber--;
			
			if(bookSize > DEFAULT_SIZE)
			{
				bookSize -= BOOK_SIZE_ADD;
			}
			else if(bookSize <= DEFAULT_SIZE)
			{
				bookSize = DEFAULT_SIZE;
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
		fade -> setAlpha(fade -> getAlpha() + FADE);
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