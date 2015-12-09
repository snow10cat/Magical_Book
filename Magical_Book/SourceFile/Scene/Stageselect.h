
#ifndef __MAGICAL_BOOK_STSGESELECT_H__
#define __MAGICAL_BOOK_STSGESELECT_H__

#include "Scene.h"
#include "CatGameLib.h"


#define SELECT_SIZE 0.35f 		//!< �I�����T�C�Y
#define DESELECT_SIZE 0.3f		//!< ��I�����T�C�Y
#define SELECT_ARROW_SIZE 0.1f	//!< ���̑I�����T�C�Y
#define SELECT_BACK_SIZE 1.2f	//!< �߂郍�S�̑I�����T�C�Y

#define FRAME_SIZE_X 0.35f		//!< �߂郍�S�I�����̃t���[��X�T�C�Y
#define FRAME_SIZE_Y 0.12f		//!< �߂郍�S�I�����̃t���[��Y�T�C�Y

#define BOOK_SIZE 1.5f	  		//!< �{�̃T�C�Y
#define BOOK_SIZE_ADD 0.1f		//!< �{�̃T�C�Y���Z�x


namespace MagicalBook
{

class StageSelect : public Scene
{
public:
	StageSelect();
	~StageSelect();

	void init(void) override;
	void update(void) override;

	enum StageSelectNumber
	{
		SelectStage,		//!< �X�e�[�W�I��
		BackAnimation,		//!< �O�ɖ߂�A�j���[�V����
		Animation,			//!< �A�j���[�V����
		Next,				//!< ����
	};

private:

	enum SelectPosition
	{
		LeftUp,			//!< ����
		RightUp,		//!< �E��
		LeftDown,		//!< ����
		RightDown,		//!< �E��
		Leftarrow,		//!< �����
		Rightarrow,		//!< �E���
		BackLogo,		//!< �߂郍�S
	};
	
	float volume;			//!< ����
	bool volumeFlag;		//!< �Đ��t���O

	int selectFlag;			//!< �I���t���O

	int counter;			//!< �J�E���^�[
	int animeNumber;		//!< �A�j���[�V�����ԍ�
	int animeCounter;		//!< �A�j���[�V�����p�J�E���^�[
	int stageSelectWork;	//!< �I���V�[��

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< ����ʒ��S
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< �c��ʒ��S

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* selectBgm;	//!< �X�e�[�W�I�����BGM
	CatGameLib::LibSound* menuSelect;	//!< �I��SE

	CatGameLib::LibSprite* fade;		//!< �t�F�[�h�p
	CatGameLib::LibSprite* floor;		//!< ��
	CatGameLib::LibSprites* books;		//!< �{���߂���
	CatGameLib::LibSprite* arrowRight;	//!< �E���
	CatGameLib::LibSprite* arrowLeft;	//!< �����
	CatGameLib::LibSprite* frame;		//!< �t���[��
	CatGameLib::LibSprite* back;		//!< �߂郍�S
	
	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< �X�e�[�W�w�i

	void playSound(void);
	void stageSelectDraw(void);
	void logoFadein(void);
	void bgFadein(void);
	void stageSelect(void);
	void selectActions(void);
	void cangeSize(void);
	void backAnimation(void);
	void bookAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__