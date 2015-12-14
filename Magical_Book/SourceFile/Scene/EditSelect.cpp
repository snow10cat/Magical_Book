
#include <cassert>
#include "../Game/ResourceManager.h"
#include "../Game/StageConfig.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "EditSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

static StageConfig* stageConfig = StageConfig::getInstance();


EditSelect::EditSelect() : sizeSection(nullptr),
						   bgSection(nullptr),
						   musicSection(nullptr)
{	
	stageBgm[ResourceManager::BGM_1] = LibSound::create("bgm/stage1.wav");
	stageBgm[ResourceManager::BGM_2] = LibSound::create("bgm/stage2.wav");
	stageBgm[ResourceManager::BGM_3] = LibSound::create("bgm/stage3.wav");

	sizeSection = CatGameLib::LibSprite::create("logo/size_section.png");
	sizeLogo[ResourceManager::Size_S] = CatGameLib::LibSprite::create("logo/S.png");
	sizeLogo[ResourceManager::Size_M] = CatGameLib::LibSprite::create("logo/M.png");
	sizeLogo[ResourceManager::Size_L] = CatGameLib::LibSprite::create("logo/L.png");

	bgSection = CatGameLib::LibSprite::create("logo/bg_section.png");
	
	musicSection = CatGameLib::LibSprite::create("logo/music_section.png");
	bgmLogos[ResourceManager::BGM_1] = CatGameLib::LibSprite::create("logo/bgm1.png");
	bgmLogos[ResourceManager::BGM_2] = CatGameLib::LibSprite::create("logo/bgm2.png");
	bgmLogos[ResourceManager::BGM_3] = CatGameLib::LibSprite::create("logo/bgm3.png");;

}


EditSelect::~EditSelect()
{
}


/**
 *	@brief ������
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::init(void)
{
	input = LibInput::getInstance();

	selectBgm = ResourceManager::getInstance() -> getSound("selectbgm");
	menuSelect = ResourceManager::getInstance() -> getSound("menuSelect");

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
	bgmCount = 0;

	setUpWork = StageSize;			//�T�C�Y�I������
	sizeCounter = EditSize::Size_S;
	bgCounter = EditBg::BG_Castle;
	bgmCounter = BACK;
	animeNumber = BOOK_ANM_MIN;
	animeCounter = 0;

	//����
	selectBgm -> setVolume(0.0f);
	selectBgm -> setLoop(true);

	for(int i = 0; i < ResourceManager::BGM_Count; i++)
	{
		stageBgm[i] -> setVolume(0.0f);
		stageBgm[i] -> setLoop(true);
	}

	menuSelect -> setVolume(MAX_VOLUME);

	//�摜
	books -> setPosition(sWHeaf - EDIT_SEL_BOOK_POS_X, sHHeaf);
	books -> setScale(BOOK_SIZE);


	//�傫�����S
	sizeSection -> setPosition(sWHeaf - 100, sHHeaf + 300);
	sizeSection -> setScale(SELECT_LOGO_SIZE);
	sizeSection -> setAlpha(0.0f);

	sizeLogo[ResourceManager::Size_S] -> setPosition(sWHeaf - 100, sHHeaf + 200);

	sizeLogo[ResourceManager::Size_M] -> setPosition(sWHeaf + 50, sHHeaf + 200);

	sizeLogo[ResourceManager::Size_L] -> setPosition(sWHeaf + 200, sHHeaf + 200);

	for(int i = 0; i <= ResourceManager::Size_Count - 1; i++)
	{
		sizeLogo[i] -> setScale(DESELECT_SIZE);
		sizeLogo[i] -> setAlpha(0.0f);
	}
	sizeLogo[0] -> setScale(SELECT_SIZE);

	//�w�i���S
	bgSection -> setPosition(sWHeaf - 100, sHHeaf + 80);
	bgSection -> setScale(LOGO_SIZE);
	bgSection -> setAlpha(0.0f);

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 100, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf - 25, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf + 50, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 125, sHHeaf - 30);

	bgTextures[ResourceManager::BG_Throne] -> setPosition(sWHeaf + 200, sHHeaf - 30);
	
	for(int i = 0; i <= ResourceManager::BG_Count - 1; i++)
	{
		bgTextures[i] -> setScale(DESELECT_BG_SIZE);
		bgTextures[i] -> setAlpha(0.0f);
	}

	//���y���S
	musicSection -> setPosition(sWHeaf - 100, sHHeaf - 140);
	musicSection -> setScale(LOGO_SIZE);
	musicSection -> setAlpha(0.0f);
	
	bgmLogos[ResourceManager::BGM_1] -> setPosition(sWHeaf - 100, sHHeaf - 220);

	bgmLogos[ResourceManager::BGM_2] -> setPosition(sWHeaf + 50, sHHeaf - 220);

	bgmLogos[ResourceManager::BGM_3] -> setPosition(sWHeaf + 200, sHHeaf - 220);
	
	for(int i = 0; i <= ResourceManager::BGM_Count - 1; i++)
	{
		bgmLogos[i] -> setScale(DESELECT_SIZE);
		bgmLogos[i] -> setAlpha(0.0f);
	}

	frame -> setPosition(sWHeaf - 100, sHHeaf + 200);
	frame -> setScale(FRAME_SIZE);
	frame -> setAlpha(0.0f);

	back -> setPosition(sWHeaf - 500, sHHeaf - 280);
	back -> setScale(LOGO_SIZE);
	back -> setAlpha(0.0f);

	//�t�F�[�h�C������
	editSetWork = Fadein;
}


/**
 *	@brief �X�V
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
		assert(!"�s���ȏ��");
		break;
	}
}


/**
 *	@brief �����Đ�
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::playSound(void)
{
	bgmCount = (bgmCounter - 1) % ResourceManager::BGM_Count;
	const int bgmNum = CatGameLib::LibBasicFunc::wrap(bgmCount, 0, 3);
	if(bgmCounter == BACK)
	{
		stageBgm[bgmNum] -> stop();
		selectBgm -> play();
	}
	else if(bgmCounter > BACK)
	{
		selectBgm -> stop();
		stageBgm[bgmNum] -> play();
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
	stageBgm[bgmNum] -> setVolume(volume);
}


/**
 *	@brief �`��
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

		//�I������Ă����͈�ԑO�ɕ`��
		if(bgCounter > 0)
		{
			const int count = (bgCounter - 1) % ResourceManager::BG_Count;
			bgTextures[count] -> draw();
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
 *	@brief ���S�t�F�[�h�C��
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::logoFadein(void)
{
	if(sizeSection -> getAlpha() < 255)
	{
		sizeSection -> setAlpha(sizeSection -> getAlpha() + FADE);
	}
	else
	{
		sizeSection -> setAlpha(255);
	}

	for(int i = 0; i < ResourceManager::Size_Count; i++)
	{
		if(sizeLogo[i] -> getAlpha() < 255)
		{
			sizeLogo[i] -> setAlpha(sizeLogo[i] -> getAlpha() + FADE);
		}
		else
		{
			sizeLogo[i] -> setAlpha(255);
		}
	}

	if(bgSection -> getAlpha() < 255)
	{
		bgSection -> setAlpha(bgSection -> getAlpha() + FADE);
	}
	else
	{
		bgSection -> setAlpha(255);
	}

	for(int i = 0; i < ResourceManager::BG_Count; i++)
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

	if(musicSection -> getAlpha() < 255)
	{
		musicSection -> setAlpha(musicSection -> getAlpha() + FADE);
	}
	else
	{
		musicSection -> setAlpha(255);
	}
	for(int i = 0; i < ResourceManager::BGM_Count; i++)
	{
		if(bgmLogos[i] -> getAlpha() < 255)
		{
			bgmLogos[i] -> setAlpha(bgmLogos[i] -> getAlpha() + FADE);
		}
		else
		{
			bgmLogos[i] -> setAlpha(255);
		}
	}

	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + FADE);
	}
	else
	{
		back -> setAlpha(255);
	}

	if(frame -> getAlpha() < 255)
	{
		frame -> setAlpha(frame -> getAlpha() + FADE);
	}
	else
	{
		frame -> setAlpha(255);
		editSetWork = EditMenuSelect;		//�I����ʂ�
	}
}


/**
 *	@brief �ݒ���
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::editSetUp(void)
{
	switch(setUpWork)
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
		assert(!"�s���ȏ��");
		break;
	}
}


/**
 *	@brief �T�C�Y�I��
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::sizeSelect(void)
{
	sizeCounter = CatGameLib::LibBasicFunc::wrap(sizeCounter, 0, EditSize::Size_Count);

	//�S�ẴX�P�[���ݒ�
	auto sizeSizeFunc = [&](void)
	{
		sizeSection -> setScale(SELECT_LOGO_SIZE);

		for(int i = 0; i < ResourceManager::Size_Count; i++)
		{
			sizeLogo[i] -> setScale(DESELECT_SIZE);
		}
		
		back -> setScale(LOGO_SIZE);
		frame -> setScale(FRAME_SIZE);
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
		if(sizeCounter % EditSize::Size_Count != BACK)
		{
			sizeSection -> setScale(LOGO_SIZE);
			setUpWork = StageBG;		//�w�i�I����
		}
		else
		{
			editSetWork = BackAnimation;		//�߂�A�j���[�V������
		}
	}

	//�I������Ă���T�C�Y���S�̃T�C�Y�ύX
	if(setUpWork == StageSize)
	{
		if(sizeCounter % EditSize::Size_Count == EditSize::Size_S)
		{
			sizeSizeFunc();
			sizeLogo[ResourceManager::Size_S] -> setScale(SELECT_SIZE);
			stageConfig -> setSizeNumber(StageConfig::Size_S);

			frame -> setPosition(sizeLogo[ResourceManager::Size_S] -> getPosition());
		}
		else if(sizeCounter % EditSize::Size_Count == Size_M)
		{
			sizeSizeFunc();
			sizeLogo[ResourceManager::Size_M] -> setScale(SELECT_SIZE);
			stageConfig -> setSizeNumber(StageConfig::Size_M);
			
			frame -> setPosition(sizeLogo[ResourceManager::Size_M] -> getPosition());
		}
		else if(sizeCounter % EditSize::Size_Count == Size_L)
		{
			sizeSizeFunc();
			sizeLogo[ResourceManager::Size_L] -> setScale(SELECT_SIZE);
			stageConfig -> setSizeNumber(StageConfig::Size_L);
			
			frame -> setPosition(sizeLogo[ResourceManager::Size_L] -> getPosition());
		}
		else if(sizeCounter % EditSize::Size_Count == BACK)
		{
			sizeSizeFunc();
			sizeSection -> setScale(LOGO_SIZE);

			back -> setScale(SELECT_LOGO_SIZE);
			frame ->setScaleX(FRAME_SIZE_X);
			frame ->setScaleY(FRAME_SIZE_Y);
			frame -> setPosition(back -> getPosition());
		}
	}
}


/**
 *	@brief �w�i�I��
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bgSelect(void)
{
	bgCounter = CatGameLib::LibBasicFunc::wrap(bgCounter, 0, EditBg::BG_Count);
	
	//�S�ẴX�P�[���ݒ�
	auto sizebgFunc = [&](void)
	{
		bgSection -> setScale(SELECT_LOGO_SIZE);
	
		for(int i = ResourceManager::BG_Castle; i < ResourceManager::BG_Count; i++)
		{
			bgTextures[i] -> setScale(DESELECT_BG_SIZE);
		}

		back -> setScale(LOGO_SIZE);
		frame -> setScale(BG_FRAME_SIZE);
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
		if(bgCounter % EditBg::BG_Count != BACK)
		{
			bgSection -> setScale(LOGO_SIZE);
			bgmCounter = EditBgm::Bgm_1;
			volumeFlag = false;
			setUpWork = StageBGM;		//BGM�I����
		}
		else
		{
			editSetWork = BackAnimation;		//�߂�A�j���[�V������
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizebgFunc();
		bgSection -> setScale(LOGO_SIZE);
		setUpWork = StageSize;		//�T�C�Y�I����
	}
	
	//�I������Ă���w�i�̃T�C�Y�ύX
	if(setUpWork == StageBG)
	{
		if(bgCounter % EditBg::BG_Count == EditBg::BG_Castle)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Castle] -> setScale(SELECT_BG_SIZE);
			frame -> setPosition(bgTextures[ResourceManager::BG_Castle] -> getPosition());

			stageConfig -> setBgNumber(StageConfig::BG_Castle);
		}
		else if(bgCounter % EditBg::BG_Count == EditBg::BG_Table)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Table] -> setScale(SELECT_BG_SIZE);
			frame -> setPosition(bgTextures[ResourceManager::BG_Table] -> getPosition());

			stageConfig -> setBgNumber(StageConfig::BG_Table);
		}
		else if(bgCounter % EditBg::BG_Count == EditBg::BG_Gate)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Gate] -> setScale(SELECT_BG_SIZE);
			frame -> setPosition(bgTextures[ResourceManager::BG_Gate] -> getPosition());
			
			stageConfig -> setBgNumber(StageConfig::BG_Gate);
		}
		else if(bgCounter % EditBg::BG_Count == EditBg::BG_Window)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Window] -> setScale(SELECT_BG_SIZE);
			frame -> setPosition(bgTextures[ResourceManager::BG_Window] -> getPosition());
			
			stageConfig -> setBgNumber(StageConfig::BG_Window);
		}
		else if(bgCounter % EditBg::BG_Count == EditBg::BG_Throne)
		{
			sizebgFunc();
			bgTextures[ResourceManager::BG_Throne] -> setScale(SELECT_BG_SIZE);
			frame -> setPosition(bgTextures[ResourceManager::BG_Throne] -> getPosition());
			
			stageConfig -> setBgNumber(StageConfig::BG_Throne);
		}
		else if(bgCounter % EditBg::BG_Count == BACK)
		{
			sizebgFunc();
			
			bgSection -> setScale(LOGO_SIZE);

			back -> setScale(SELECT_LOGO_SIZE);
			frame ->setScaleX(FRAME_SIZE_X);
			frame ->setScaleY(FRAME_SIZE_Y);
			frame -> setPosition(back -> getPosition());
		}
	}
}


/**
 *	@brief ���y�I��
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bgmSelect(void)
{
	bgmCounter = CatGameLib::LibBasicFunc::wrap(bgmCounter, 0, EditBgm::Bgm_Count);
	
	//�S�ẴX�P�[���ݒ�
	auto sizeBgmFunc = [&](void)
	{
		musicSection -> setScale(SELECT_LOGO_SIZE);

		for(int i = 0; i < ResourceManager::BGM_Count; i++)
		{
			bgmLogos[i] -> setScale(DESELECT_SIZE);
		}
		
		back -> setScale(LOGO_SIZE);
		frame -> setScale(FRAME_SIZE);
	};

	if(volume == 0 && volumeFlag == false)
	{
		volumeFlag = true;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		menuSelect -> play();
		bgmCounter--;
		volumeFlag = false;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		menuSelect -> play();
		bgmCounter++;
		volumeFlag = false;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		if(bgmCounter % EditBgm::Bgm_Count !=BACK)
		{
			musicSection -> setScale(LOGO_SIZE);
			editSetWork = Animation;		//�A�j���[�V������
		}
		else
		{
			editSetWork = BackAnimation;	//�߂�A�j���[�V������
		}
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		sizeBgmFunc();
		musicSection -> setScale(LOGO_SIZE);
		setUpWork = StageBG;		//�w�i�I����
	}
	
	//�I������Ă���BGM���S�̃T�C�Y�ύX
	if(setUpWork == StageBGM)
	{
		if(bgmCounter % EditBgm::Bgm_Count == EditBgm::Bgm_1)
		{
			sizeBgmFunc();
			bgmLogos[ResourceManager::BGM_1] -> setScale(SELECT_SIZE);
			
			frame -> setPosition(bgmLogos[ResourceManager::BGM_1] -> getPosition());
			
			stageConfig -> setMusicNumber(StageConfig::BGM_1);
		}
		else if(bgmCounter % EditBgm::Bgm_Count == EditBgm::Bgm_2)
		{
			sizeBgmFunc();
			bgmLogos[ResourceManager::BGM_2] -> setScale(SELECT_SIZE);
			
			frame -> setPosition(bgmLogos[ResourceManager::BGM_2] -> getPosition());
			
			stageConfig -> setMusicNumber(StageConfig::BGM_2);
		}
		else if(bgmCounter % EditBgm::Bgm_Count == EditBgm::Bgm_3)
		{
			sizeBgmFunc();
			bgmLogos[ResourceManager::BGM_3] -> setScale(SELECT_SIZE);
			
			frame -> setPosition(bgmLogos[ResourceManager::BGM_3] -> getPosition());
			
			stageConfig -> setMusicNumber(StageConfig::BGM_3);
		}
		else if(bgmCounter % EditBgm::Bgm_Count == BACK)
		{
			sizeBgmFunc();
			musicSection -> setScale(LOGO_SIZE);

			back -> setScale(SELECT_LOGO_SIZE);
			frame ->setScaleX(FRAME_SIZE_X);
			frame ->setScaleY(FRAME_SIZE_Y);
			frame -> setPosition(back -> getPosition());
		}
	}
}


/**
 *	@brief �{��(1�O�ɂ̃V�[����)�ړ�������A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::backAnimation(void)
{
	volumeFlag = false;

	if (books -> getPositionX() < sWHeaf + BOOK_POS_X)
	{
		books -> setPositionX(books -> getPositionX() + MOVEMENT_BOOK);
	}
	else
	{
		books -> setPositionX(sWHeaf + BOOK_POS_X);
		editSetWork = Next;			//���j���[�Z���N�g��
	}
}


/**
 *	@brief �{���߂���A�j���[�V����
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::bookAnimation(void)
{
	volumeFlag = false;

	if(animeNumber < BOOK_ANM_MAX)
	{
		animeCounter = CatGameLib::LibBasicFunc::wrap(animeCounter, 0, BOOK_ANIM_SPEED);
		animeCounter++;
		if(animeCounter % BOOK_ANIM_SPEED == 0)
		{
			animeCounter = 0;
			animeNumber++;
		}
	}
	else
	{
		animeNumber = BOOK_ANM_MIN;
	}

	if (books -> getPositionX() < sWHeaf + EDIT_BOOK_POS_X)
	{
		books -> setPositionX(books -> getPositionX() + MOVEMENT_BOOK);
	}
	else
	{
		if(animeNumber == BOOK_ANM_MIN)
		{
			books -> setPositionX(sWHeaf + EDIT_BOOK_POS_X);
			editSetWork = Next;		//�G�f�B�b�g��ʂ�
		}
	}
}


/**
 *	@brief �eCounter��BACK�Ȃ烁�j���[�Z���N�g�ցA����ȊO�Ȃ�G�f�B�b�g��
 *
 *	@author	Tatsuya Maeda
 */
void EditSelect::next(void)
{
	LibSound::allStop();

	if(sizeCounter == BACK || bgCounter == BACK || bgmCounter == BACK)
	{
		//���j���[�Z���N�g��
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::MenuSelect);
	}
	else
	{
		//�G�f�B�b�g��
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::Edit);
	}
}