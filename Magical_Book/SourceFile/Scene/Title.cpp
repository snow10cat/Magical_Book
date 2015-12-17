
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Title.h"


using namespace CatGameLib;
using namespace MagicalBook;


Title::Title() : titleBgm(nullptr),
				 gameIn(nullptr),
				 titleLogo(nullptr),
				 titleStart(nullptr),
				 titleEnd(nullptr)
{
	titleBgm = LibSound::create("bgm/title.wav");
	gameIn = LibSound::create("se/in.wav");
	titleLogo = LibSprite::create("logo/title_logo.png");
	titleStart = LibSprite::create("logo/title_start.png");
	titleEnd = LibSprite::create("logo/title_end.png");
}


Title::~Title()
{
}


/**
 *	@brief ������
 *
 *	@author	Tatsuya Maeda
 */
void Title::init(void)
{
	input = LibInput::getInstance();
	menuSelect = ResourceManager::getInstance() -> getSound("menuSelect");
	fade = ResourceManager::getInstance() ->getSprite("fade");
	floor = ResourceManager::getInstance() ->getSprite("floor");
	openBooks = ResourceManager::getInstance() -> getSprites("openBook");

	
	volume = MAX_VOLUME;
	volumeFlag = true;
	
	timer = 0;
	size = DEFAULT_SIZE;
	logoFlag = 1;
	bookSize = DEFAULT_SIZE;
	counter = 0;
	flag = true;
	animeNumber = BOOK_ANM_MIN;

	//����
	titleBgm -> setVolume(volume);
	titleBgm -> setLoop(true);

	menuSelect -> setVolume(volume);

	gameIn -> setVolume(volume);

	//�摜
	fade -> setPosition(sWHeaf, sHHeaf);
	fade -> setScale(DEFAULT_SIZE);
	fade -> setAlpha(0.0f);

	floor -> setPosition(sWHeaf, sHHeaf);
	floor -> setScale(DEFAULT_SIZE);

	openBooks -> setPosition(sWHeaf - TITLE_BOOK_POS_X, sHHeaf);
	openBooks -> setScale(bookSize);

	titleLogo -> setPosition(sWHeaf + 25, sHHeaf + 150);
	titleLogo -> setScale(0.5f);

	titleStart -> setPosition(sWHeaf + 25, sHHeaf - 50);
	titleStart -> setScale(DEFAULT_SIZE);

	titleEnd -> setPosition(sWHeaf + 25, sHHeaf - 150);
	titleEnd -> setScale(DEFAULT_SIZE);

	//�I������
	titleWork = Select;
}


/**
 *	@brief �X�V
 *
 *	@author	Tatsuya Maeda
 */
void Title::update(void)
{
	playSound();

	titleDraw();

	switch (titleWork)
	{
	case Select:
		select();
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
void Title::playSound(void)
{
	if (titleBgm -> getState() != LibSound::Play)
	{
		titleBgm -> play();
	}

	//BGM�̃t�F�[�h�A�E�g
	if (volumeFlag == false)
	{
		volume -= BGM_FADE;
	}
	titleBgm -> setVolume(volume);
}


/**
 *	@brief �`��
 *
 *	@author	Tatsuya Maeda
 */
void Title::titleDraw(void)
{
	floor -> draw();
	openBooks -> draw(animeNumber);
	
	if(titleWork == Select)
	{
		titleLogo -> draw();
		titleStart -> draw();
		titleEnd -> draw();
	}
	
	fade -> draw();
}


/**
 *	@brief ���[�h�I��
 *
 *	@author	Tatsuya Maeda
 */
void Title::select(void)
{
	counter = LibBasicFunc::wrap(counter, 0, 2);

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		menuSelect -> play();
		timer = 0;
		size = DEFAULT_SIZE;
		logoFlag = 1;
		counter++;
	}

	if (counter % 2 == 0)
	{
		logoAnimation();

		titleStart -> setScale(size);
		titleEnd -> setScale(LOGO_MIN_SIZE);

		//�Q�[���{��
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			timer = 0;
			size = DEFAULT_SIZE;
			counter = 0;
			titleWork = Animation;		//�A�j���[�V������
		}
	}
	else if (counter % 2 == 1)
	{
		logoAnimation();
		
		titleStart -> setScale(LOGO_MIN_SIZE);
		titleEnd -> setScale(size);

		//�Q�[���I��
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			exit(0);
		}
	}
}


/**
 *	@brief ���S�A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void Title::logoAnimation(void)
{
	timer = LibBasicFunc::wrap(timer, 0, 3);

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
 *	@brief �{�ړ��A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void Title::animation(void)
{
	volumeFlag = false;

	bookAnimation();

	if (openBooks -> getPositionX() < sWHeaf + BOOK_POS_X)
	{
		openBooks -> setPositionX(openBooks -> getPositionX() + MOVEMENT_BOOK);
	}
	else
	{
		openBooks -> setPositionX(sWHeaf + BOOK_POS_X);

		if(animeNumber == BOOK_ANM_MAX)
		{
			titleWork = Fadeout;		//�t�F�[�h�A�E�g��
		}
	}
}


/**
 *	@brief �{�̊J���A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void Title::bookAnimation(void)
{
	if(animeNumber < BOOK_ANM_MAX)
	{
		counter = LibBasicFunc::wrap(counter, 0, BOOK_ANIM_SPEED);
		counter++;
		if(counter % BOOK_ANIM_SPEED == 0)
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
void Title::fadeout(void)
{
	openBooks -> setScale(bookSize);
	if(fade -> getAlpha() < 255)
	{
		fade -> setAlpha(fade -> getAlpha() + FADE);
	}
	else
	{
		fade -> setAlpha(255);
	}

	if(flag == true)
	{
		gameIn -> play();
		flag = false;
	}
	else if(flag == false && gameIn -> getState() != LibSound::Play)
	{
		titleWork = Next;		//���j���[�Z���N�g��
	}

	if(bookSize <= BOOK_MAX_SIZE)
	{
		bookSize += BOOK_SIZE_ADD;
	}
	else
	{
		bookSize = BOOK_MAX_SIZE;
	}
}


/**
 *	@brief ���̃V�[����
 *
 *	@author	Tatsuya Maeda
 */
void Title::next(void)
{
	LibSound::allStop();		//���ׂẴT�E���h��~
	//���j���[�Z���N�g��
	SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
}
