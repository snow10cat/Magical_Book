
#ifndef __MAGICAL_BOOK_MENUSELECT_H__
#define __MAGICAL_BOOK_MENUSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

#define LOGO_ANIM_SPEED 3
#define LOGO_MAX_SIZE 1.3f
#define LOGO_MIN_SIZE 0.8f
#define LOGO_SIZE_ADD 0.01f

#define BOOK_SIZE 1.5f
#define BOOK_SIZE_ADD 0.01f

namespace MagicalBook
{

class MenuSelect : public Scene
{
public:
	MenuSelect();
	~MenuSelect();

	void init(void) override;
	void update(void) override;

	enum MenuSelectNumber
	{
		Fadein,			//!< �t�F�[�h�C��
		ModeSelect,		//!< ���[�h�I��
		Animation,		//!< �A�j���[�V����
		Fadeout,		//!< �t�F�[�h�A�E�g
		Next,			//!< ����
	};

private:
	
	float volume;		//!< ����
	bool volumeFlag;	//!< �Đ��t���O

	int timer;			//!< ���S�A�j���[�V�����^�C�}�[
	int logoFlag;		//!< ���S�t���O
	int counter;		//!< �J�E���^�[
	bool flag;			//!< �����̐؂�ւ�
	bool fadeFlag;		//!< �t�F�[�h�p�t���O
	int animeNumber;	//!< �A�j���[�V�����ԍ�
	int animeCounter;	//!< �A�j���[�V�����p�J�E���^�[
	int selectWork;		//!< �I���V�[��
	float size;			//!< ���S�T�C�Y

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< ����ʒ��S
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< �c��ʒ��S

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;	//!< ���[�h�I�����BGM
	CatGameLib::LibSound* menuSelect;	//!< �I��SE

	CatGameLib::LibSprite* fade;		//!< �t�F�[�h�p
	CatGameLib::LibSprite* floor;		//!< ��
	CatGameLib::LibSprites* openBooks;	//!< �{���J��
	CatGameLib::LibSprites* books;		//!< �{���߂���
	CatGameLib::LibSprite* play;		//!< �V�ԃ��S
	CatGameLib::LibSprite* make;		//!< ��郍�S
	CatGameLib::LibSprite* back;		//!< �߂郍�S

	void playSound(void);
	void menuSelectDraw(void);
	void fadein(void);
	void logoFadein(void);
	void modeSelect(void);
	void logoAnimation(void);
	void animation(void);
	void bookAnimation(void);
	void closeAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif //!<  __MAGICAL_BOOK_STSGESELECT_H__