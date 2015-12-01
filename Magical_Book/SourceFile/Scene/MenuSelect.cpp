
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


//������
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
	fadeFlag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;
	size = 1.3;

	//����
	selectBgm -> setVolume(volume);
	selectBgm -> setLoop(true);

	menuSelect -> setVolume(1.0f);

	//�摜
	fade -> setAlpha(255);

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

	//�t�F�[�h�C������
	select_work = Fadein;
}


//�X�V
void MenuSelect::update(void)
{
	playSound();

	menuSelectDraw();

	switch(select_work)
	{
	case Fadein:
		if(SceneManager::getInstance() -> getOldSceneNumber() == SceneManager::SceneNumber::Title)
		{
			fadein();
		}
		else
		{
			select_work = ModeSelect;
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


//�����Đ�
void MenuSelect::playSound(void)
{
	if(selectBgm -> getState() != LibSound::Play)
	{
		selectBgm -> play();
	}

	if(volumeFlag == false)
	{
		//BGM�t�F�[�h�A�E�g
		volume -= 0.02f;
		selectBgm -> setVolume(volume);
	}
	else if(volume <= 1.0 && volumeFlag == true)
	{
		//BGM�t�F�[�h�C��
		volume += 0.02f;
		selectBgm -> setVolume(volume);
	}
}


//�`��
void MenuSelect::menuSelectDraw(void)
{
	floor -> draw();

	if(select_work == Animation && counter == 2)
	{
		openBooks -> draw(anime_number);
	}
	else
	{
		books -> draw(anime_number);
	}

	if(select_work == Fadein || select_work == ModeSelect)
	{
		play -> draw();
		make -> draw();
		back -> draw();
	}

	fade -> draw();
}


//�t�F�[�h�C��
void MenuSelect::fadein(void)
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
	}

	if(fade -> getAlpha() > 0)
	{
		fade -> setAlpha(fade -> getAlpha() - 5);
	}
	else
	{
		fade -> setAlpha(0);
		select_work = ModeSelect;
	}
}


//���[�h�I��
void MenuSelect::modeSelect(void)
{
	counter = CatGameLib::LibBasicFunc::wrap(counter, 0, 3);

	if(bookAnmFlag == 0)
	{
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
				select_work = Animation;		//�A�j���[�V������
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
				select_work = Animation;		//�A�j���[�V������
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
				anime_number = BOOK_ANM_MAX;
				size = 1.5f;
				select_work = Animation;		//�A�j���[�V������
				bookAnmFlag = 1;
			}
		}
	}
}


//���S�A�j���[�V����
void MenuSelect::logoAnimation()
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


//�ڍs�A�j���[�V����
void MenuSelect::animation(void)
{	
	volumeFlag = false;

	if(counter == 0)
	{
		bookAnimation();

		if(anime_number == BOOK_ANM_MAX)
		{
			anime_number = BOOK_ANM_MIN;
			anime_counter = 0;
			select_work = Next;
		}
	}
	else if(counter == 1)
	{
		if (books -> getPositionX() > sWHeaf - 320)
		{
			books -> setPositionX(books -> getPositionX() - 10);
		}
		else
		{
			books -> setPositionX(sWHeaf - 320);
			select_work = Next;
		}
	}
	else
	{
		openBooks -> setScale(size);

		if (openBooks -> getPositionX() > sWHeaf - 250)
		{
			openBooks -> setPositionX(openBooks -> getPositionX() - 10);
		}
		else
		{
			openBooks -> setPositionX(sWHeaf - 250);
		}

		if(anime_number > BOOK_ANM_MIN)
		{
			closeAnimation();
		}

		if(size == 1.0 && anime_number == BOOK_ANM_MIN)
		{
			if(anime_number == BOOK_ANM_MIN)
			{
				fadeout();
				fadein();
				
				if()
				{
					select_work = Next;
				}
			}
		}
	}
}


//�{���߂���A�j���[�V����
void MenuSelect::bookAnimation()
{
	if(anime_number <= BOOK_ANM_MAX)
	{
		anime_counter = CatGameLib::LibBasicFunc::wrap(anime_counter, 0, 7);
		anime_counter++;
		if(anime_counter % 7 == 0)
		{
			anime_counter = 0;
			anime_number++;
		}
	}
}


//�{�����A�j���[�V����
void MenuSelect::closeAnimation(void)
{
	if(anime_number >= BOOK_ANM_MIN)
	{
		anime_counter = CatGameLib::LibBasicFunc::wrap(anime_counter, 0, 7);
		anime_counter++;
		if(anime_counter % 7 == 0)
		{
			anime_counter = 0;
			anime_number--;
			
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
}


//�t�F�[�h�A�E�g
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


//counter��0�Ȃ�X�e�[�W�Z���N�g�A1�Ȃ�G�f�B�b�g�Z���N�g�ցA����ȊO�̓^�C�g����
void MenuSelect::next(void)
{
	LibSound::allStop();		//���ׂẴT�E���h��~
	if(counter == 0)
	{
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::StageSelect);
	}
	else if(counter == 1)
	{
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}
	else
	{
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Title);
	}
}