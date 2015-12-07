
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
 *	@brief ������
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
	logoFlag = 1;
	counter = 0;
	flag = true;
	fadeFlag = true;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;
	size = 1.3;

	//����
	selectBgm -> setVolume(volume);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(1.0f);

	//�摜
	if(SceneManager::getInstance() -> getOldSceneNumber() == SceneManager::SceneNumber::Title)
	{
		fade -> setAlpha(255);
	}
	else
	{
		fade -> setAlpha(0);
	}

	books -> setPosition(sWHeaf + 300, sHHeaf);
	books -> setScale(BOOK_SIZE);

	openBooks -> setPosition(sWHeaf + 300, sHHeaf);
	openBooks -> setScale(BOOK_SIZE);

	play -> setPosition(sWHeaf - 100, sHHeaf + 200);
	play -> setScale(1.3f);
	play -> setAlpha(0.0f);

	make -> setPosition(sWHeaf - 100, sHHeaf);
	make -> setScale(1.0f);
	make -> setAlpha(0.0f);

	back -> setPosition(sWHeaf - 100, sHHeaf - 200);
	back -> setScale(1.0f);
	back -> setAlpha(0.0f);

	//�t�F�[�h�C������
	selectWork = Fadein;
}


/**
 *	@brief �X�V
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
		assert(!"�s���ȏ��");
		break;
	}
}


/**
 *	@brief �����Đ�
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
		//BGM�t�F�[�h�A�E�g
		volume -= VOICE_FADE;
		selectBgm -> setVolume(volume);
	}
	else if(volume <= 1.0 && volumeFlag == true)
	{
		//BGM�t�F�[�h�C��
		volume += VOICE_FADE;
		selectBgm -> setVolume(volume);
	}
}


/**
 *	@brief �`��
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
 *	@brief �t�F�[�h�C��
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
 *	@brief ���S�t�F�[�h�C��
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
 *	@brief ���[�h�I��
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
		size = 1.3;
	}
	else if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		menuSelect -> play();
		timer = 0;
		counter++;
		logoFlag = 1;
		size = 1.3;
	}

	if (counter % 3 == 0)
	{
		//�Q�[���{��
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
			selectWork = Animation;		//�A�j���[�V������
		}
	}
	else if (counter % 3 == 1)
	{
		//�Q�[���G�f�B�b�g
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
			selectWork = Animation;		//�A�j���[�V������
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
			selectWork = Animation;		//�A�j���[�V������
		}
	}
}


/**
 *	@brief ���S�A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::logoAnimation(void)
{
	timer = CatGameLib::LibBasicFunc::wrap(timer, 0, 3);

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
 *	@brief �ڍs�A�j���[�V����
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
			selectWork = Next;		//�X�e�[�W�I����
		}
	}
	else if(counter == 1)
	{
		//�{�̈ړ�
		if (books -> getPositionX() > sWHeaf - 320)
		{
			books -> setPositionX(books -> getPositionX() - 10);
		}
		else
		{
			books -> setPositionX(sWHeaf - 320);
			selectWork = Next;		//�G�f�B�b�g�I����
		}
	}
	else
	{
		openBooks -> setScale(size);

		//�{�̈ړ�
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
				selectWork = Next;		//�^�C�g����
			}
		}
	}
}


/**
 *	@brief �{���߂���A�j���[�V����
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
 *	@brief �{�����A�j���[�V����
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
 *	@brief �t�F�[�h�A�E�g
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
 *	@brief counter��0�Ȃ�X�e�[�W�Z���N�g�A1�Ȃ�G�f�B�b�g�Z���N�g�ցA����ȊO�̓^�C�g����
 *
 *	@author	Tatsuya Maeda
 */
void MenuSelect::next(void)
{
	LibSound::allStop();		//���ׂẴT�E���h��~
	if(counter == 0)
	{
		//�X�e�[�W�Z���N�g��
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::StageSelect);
	}
	else if(counter == 1)
	{
		//�G�f�B�b�g�Z���N�g��
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}
	else
	{
		//�^�C�g����
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Title);
	}
}