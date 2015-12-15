
#include <cassert>
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "StageSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


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
 *	@brief ������
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::init(void)
{
	input = LibInput::getInstance();

	selectBgm = ResourceManager::getInstance() -> getSound("selectbgm");
	menuSelect = ResourceManager::getInstance() -> getSound("menuSelect");

	fade = ResourceManager::getInstance() ->getSprite("fade");
	floor = ResourceManager::getInstance() ->getSprite("floor");
	books = ResourceManager::getInstance() -> getSprites("books");
	frame = ResourceManager::getInstance() -> getSprite("frame");
	back = ResourceManager::getInstance() -> getSprite("back");

	for(int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back(ResourceManager::getInstance() -> getSprite(bgName.c_str()));
	}

	volume = 0;
	volumeFlag = true;

	selectFlag = 0;
	counter = 0;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;

	//����
	selectBgm -> setVolume(0.0f);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(MAX_VOLUME);

	//�摜
	fade -> setAlpha(255);

	books -> setPosition(sWHeaf + BOOK_POS_X, sHHeaf);
	books -> setScale(BOOK_SIZE);

	frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
	frame -> setScale(SELECT_SIZE);
	frame -> setAlpha(0.0f);

	arrowRight -> setPosition(sWHeaf + 150, sHHeaf - 310);
	arrowRight -> setScale(DESELECT_SIZE);
	arrowRight -> setAlpha(0.0f);

	arrowLeft -> setPosition(sWHeaf - 270, sHHeaf - 310);
	arrowLeft -> setScale(DESELECT_SIZE);
	arrowLeft -> setAlpha(0.0f);

	back -> setPosition(sWHeaf + 500, sHHeaf - 300);
	back -> setScale(DEFAULT_SIZE);
	back -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 210, sHHeaf + 160);
	bgTextures[ResourceManager::BG_Castle] -> setScale(DESELECT_SIZE);
	bgTextures[ResourceManager::BG_Castle] -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf + 90, sHHeaf + 160);
	bgTextures[ResourceManager::BG_Table] -> setScale(DESELECT_SIZE);
	bgTextures[ResourceManager::BG_Table] -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf - 210, sHHeaf - 140);
	bgTextures[ResourceManager::BG_Gate] -> setScale(DESELECT_SIZE);
	bgTextures[ResourceManager::BG_Gate] -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 90, sHHeaf - 140);
	bgTextures[ResourceManager::BG_Window] -> setScale(DESELECT_SIZE);
	bgTextures[ResourceManager::BG_Window] -> setAlpha(0.0f);

	//�X�e�[�W�I������
	stageSelectWork = SelectStage;
}


/**
 *	@brief �X�V
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
		assert(!"�s���ȏ��");
		break;
	}
}


/**
 *	@brief �����Đ�
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
		//�t�F�[�h�A�E�g
		volume -= BGM_FADE;
	}
	else if(volume <= MAX_VOLUME && volumeFlag == true)
	{
		//�t�F�[�h�C��
		volume += BGM_FADE;
	}
	selectBgm -> setVolume(volume);
}


/**
 *	@brief �`��
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
 *	@brief ���S�t�F�[�h�C��
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::logoFadein(void)
{
	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + FADE);
	}
	else
	{
		back -> setAlpha(255);
	}

	if(arrowRight -> getAlpha() < 255)
	{
		arrowRight -> setAlpha(arrowRight -> getAlpha() + FADE);
	}
	else
	{
		arrowRight -> setAlpha(255);
	}

	if(arrowLeft -> getAlpha() < 255)
	{
		arrowLeft -> setAlpha(arrowLeft -> getAlpha() + FADE);
	}
	else
	{
		arrowLeft -> setAlpha(255);
	}

	if(frame -> getAlpha() < 255)
	{
		frame -> setAlpha(frame -> getAlpha() + FADE);
	}
	else
	{
		frame -> setAlpha(255);
	}
}


/**
 *	@brief �X�e�[�W�w�i�t�F�[�h�C��
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::bgFadein(void)
{
	for(int i = 0; i < ResourceManager::BG_Count - 1; i++)
	{
		if(bgTextures[i] -> getAlpha() < 255)
		{
			bgTextures[i] -> setAlpha(bgTextures[i] -> getAlpha() + FADE);
		}
		else
		{
			bgTextures[i] -> setAlpha(255);
		}
	}
}


/**
 *	@brief �X�e�[�W�I��
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::stageSelect(void)
{
	changeSize();

	if(frame -> getAlpha() == 255)
	{
		selectActions();
	}
}


/**
 *	@brief �I�𑀍�
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
 *	@brief �X�e�[�W�w�i�A���S�̃T�C�Y�ύX
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::changeSize(void)
{
	//�S�ẴX�P�[���ݒ�
	auto sizeResetFunc = [&](void)
	{
		for(int i = 0; i < ResourceManager::BG_Count - 1; i++)
		{
			bgTextures[i] -> setScale(DESELECT_SIZE);
		}
		
		arrowLeft -> setScale(DESELECT_SIZE);
		arrowRight -> setScale(DESELECT_SIZE);
		back -> setScale(DEFAULT_SIZE);
		frame -> setScale(SELECT_SIZE);
	};


	switch(selectFlag)
	{
	case LeftUp:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Castle] -> setScale(SELECT_SIZE);

		frame -> setPosition(bgTextures[ResourceManager::BG_Castle] -> getPosition());
		break;
	case RightUp:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Table] -> setScale(SELECT_SIZE);

		frame -> setPosition(bgTextures[ResourceManager::BG_Table] -> getPosition());
		break;
	case LeftDown:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Gate] -> setScale(SELECT_SIZE);

		frame -> setPosition(bgTextures[ResourceManager::BG_Gate] -> getPosition());
		break;
	case RightDown:
		sizeResetFunc();

		bgTextures[ResourceManager::BG_Window] -> setScale(SELECT_SIZE);

		frame -> setPosition(bgTextures[ResourceManager::BG_Window] -> getPosition());
		break;
	case Leftarrow:
		sizeResetFunc();

		arrowLeft -> setScale(SELECT_SIZE);

		frame -> setScale(SELECT_ARROW_SIZE);
		frame -> setPosition(arrowLeft -> getPosition());
		break;
	case Rightarrow:
		sizeResetFunc();

		arrowRight -> setScale(SELECT_SIZE);

		frame -> setScale(SELECT_ARROW_SIZE);
		frame -> setPosition(arrowRight -> getPosition());
		break;
	case BackLogo:
		sizeResetFunc();

		back -> setScale(SELECT_BACK_SIZE);

		frame -> setScaleX(FRAME_SIZE_X);
		frame -> setScaleY(FRAME_SIZE_Y);
		frame -> setPosition(back -> getPosition());
		break;
	default:
		assert(!"�s���ȏ��");
		break;
	}
}


/**
 *	@brief �{���߂���(1�y�[�W�߂�)�A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::backAnimation(void)
{
	volumeFlag = false;

	if(animeNumber > BOOK_ANM_MIN)
	{
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, BOOK_ANIM_SPEED);
		animeCounter++;
		if(animeCounter % BOOK_ANIM_SPEED == 0)
		{
			animeNumber--;
		}
	}
	else
	{
		animeNumber = BOOK_ANM_MIN;
		stageSelectWork = Next;			//���j���[�Z���N�g��
	}
}


/**
 *	@brief �{���߂���A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::bookAnimation(void)
{
	volumeFlag = false;

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
 *	@brief �t�F�[�h�A�E�g
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::fadeout(void)
{
	if(fade -> getAlpha() < 255)
	{
		fade -> setAlpha(fade -> getAlpha() + FADE);
	}
	else
	{
		fade -> setAlpha(255);
		stageSelectWork = Next;		//�Q�[����
	}
}


/**
 *	@brief selectFlag��BackLogo�Ȃ烁�j���[�Z���N�g�ցA����ȊO�̓Q�[����
 *
 *	@author	Tatsuya Maeda
 */
void StageSelect::next(void)
{
	LibSound::allStop();

	if(selectFlag != BackLogo)
	{
		//�Q�[����
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Game);
	}
	else
	{
		//���j���[�Z���N�g��
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
	}

}
