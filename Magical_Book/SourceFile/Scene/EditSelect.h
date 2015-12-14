
#ifndef __MAGICAL_BOOK_EDITSELECT_H__
#define __MAGICAL_BOOK_EDITSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"


#define LOGO_SIZE 0.7f			//!< ���S�T�C�Y
#define SELECT_LOGO_SIZE 0.8f	//!< �I�����S�T�C�Y
#define SELECT_BACK_SIZE 1.2f	//!< �߂郍�S�̑I�����T�C�Y

#define SELECT_SIZE 0.35f 		//!< �I�����̑傫���A���y�T�C�Y
#define DESELECT_SIZE 0.25f		//!< ��I�����̑傫���A���y�T�C�Y

#define SELECT_BG_SIZE 0.2f		//!< �I�����̔w�i�T�C�Y
#define DESELECT_BG_SIZE 0.1f	//!< ��I�����̔w�i�T�C�Y

#define FRAME_SIZE 0.15f		//!< �t���[���T�C�Y
#define BG_FRAME_SIZE 0.2f		//!< �w�i�p�t���[���T�C�Y
#define FRAME_SIZE_X 0.3f		//!< �߂郍�S�I�����̃t���[��X�T�C�Y
#define FRAME_SIZE_Y 0.1f		//!< �߂郍�S�I�����̃t���[��Y�T�C�Y

#define BOOK_SIZE 1.5f			//!< �{�̃T�C�Y

#define BACK 0					//!< �߂�


namespace MagicalBook
{

class EditSelect : public Scene
{
public:
	EditSelect ();
	~EditSelect ();

	void init(void) override;
	void update(void) override;

	enum EditSelectNumber
	{
		Fadein,				//!< �t�F�[�h�C��
		EditMenuSelect,		//!< �G�f�B�b�g���j���[�I��
		BackAnimation,		//!< �O�ɖ߂�A�j���[�V����
		Animation,			//!< ���ɍs���A�j���[�V����
		Next,				//!< ����
	};
private:

	enum EditMenu
	{
		StageSize,			//!< �T�C�Y�I��
		StageBG,			//!< �w�i�I��
		StageBGM,			//!< ���y�I��
	};
	
	enum EditSize
	{
		//0��BACK
		Size_S = 1,			//!< S�T�C�Y
		Size_M,				//!< M�T�C�Y
		Size_L,				//!< L�T�C�Y
		Size_Count			//!< �傫���̐� + 1(BACK�̕�)
	};

	enum EditBg
	{
		//0��BACK
		BG_Castle = 1,		//!< �w�i(��O)
		BG_Table,			//!< �w�i(��)
		BG_Gate,			//!< �w�i(��)
		BG_Window,			//!< �w�i(��)
		BG_Throne,			//!< �w�i(�ʍ�)
		BG_Count			//!< �w�i�̐� + 1(BACK�̕�)
	};

	enum EditBgm
	{
		//0��BACK
		Bgm_1 = 1,			//!< ���y1
		Bgm_2,				//!< ���y2
		Bgm_3,				//!< ���y3
		Bgm_Count			//!< ���y�̐� + 1(BACK�̕�)
	};

	float volume;			//!< ����
	bool volumeFlag;		//!< �Đ��t���O
	int bgmCount;			//!< BGM�J�E���g

	int setUpWork;			//!< �ݒ�V�[��
	int sizeCounter;		//!< �傫���̃J�E���^�[
	int bgCounter;			//!< �w�i�̃J�E���^�[ 
	int bgmCounter;			//!< ���y�̃J�E���^�[
	int animeNumber;		//!< �A�j���[�V�����ԍ�
	int animeCounter;		//!< �A�j���[�V�����p�J�E���^�[

	int editSetWork;		//!< �G�f�B�b�g�I���V�[��

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< ����ʒ��S
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< �c��ʒ��S

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;		//!< �X�e�[�W�I�����BGM
	CatGameLib::LibSound* stageBgm[3];		//!< �X�e�[�WBGM
	CatGameLib::LibSound* menuSelect;		//!< �I��SE

	CatGameLib::LibSprite* floor;			//!< ��
	CatGameLib::LibSprites* books;			//!< �{���߂���
	CatGameLib::LibSprite* sizeSection;		//!< �傫�����S
	CatGameLib::LibSprite* sizeLogo[3];		//!< S, M, L���S
	CatGameLib::LibSprite* bgmLogos[3];		//!< BGM���S
	CatGameLib::LibSprite* bgSection;		//!< �w�i���S
	CatGameLib::LibSprite* musicSection;	//!< ���y���S
	CatGameLib::LibSprite* frame;			//!< �t���[��
	CatGameLib::LibSprite* back;			//!< �߂郍�S

	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< �X�e�[�W�w�i

	void playSound(void);
	void editSetUpDraw(void);
	void logoFadein(void);
	void editSetUp(void);
	void sizeSelect(void);
	void bgSelect(void);
	void bgmSelect(void);
	void backAnimation(void);
	void bookAnimation(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__