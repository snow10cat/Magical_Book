
#ifndef __MAGICAL_BOOK_TITLE_H__
#define __MAGICAL_BOOK_TITLE_H__

#include "Scene.h"
#include "CatGameLib.h"


#define LOGO_MAX_SIZE 1.1f		//!< ���S�̍ő�T�C�Y
#define LOGO_MIN_SIZE 0.9f		//!< ���S�̍ŏ��T�C�Y
#define LOGO_ANIM_SPEED 3		//!< ���S�̃A�j���[�V�������x
#define LOGO_SIZE_ADD 0.01f		//!< ���S�̃T�C�Y���Z�l

#define BOOK_MAX_SIZE 1.5f		//!< �{�̃T�C�Y
#define BOOK_SIZE_ADD 0.01f		//!< �{�̃T�C�Y���Z�x


namespace MagicalBook
{

class Title : public Scene
{
public:
	Title();
	~Title();

	void init(void) override;
	void update(void) override;


	enum TitleNumber
	{
		Select,		//!< �I��
		Animation,	//!< �A�j���[�V����
		Fadeout,	//!< �t�F�[�h�A�E�g
		Next,		//!< ����
	};
private:	
	
	float volume;		//!< ����
	bool volumeFlag;	//!< �Đ��t���O

	int timer;			//!< ���S�A�j���[�V�����^�C�}�[
	float size;			//!< ���S�T�C�Y
	int logoFlag;		//!< ���S�t���O
	float bookSize;		//!< �{�T�C�Y
	int counter;		//!< �J�E���^�[
	bool flag;			//!< �����̐؂�ւ�
	int animeNumber;	//!< �A�j���[�V�����ԍ�
	int titleWork;		//!< �^�C�g���V�[��
	
	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< ����ʒ��S
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< �c��ʒ��S

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* titleBgm;		//!< �^�C�g��BGM
	CatGameLib::LibSound* menuSelect;	//!< �I��SE
	CatGameLib::LibSound* gameIn;		//!< ����SE

	CatGameLib::LibSprite* fade;		//!< �t�F�[�h
	CatGameLib::LibSprite* floor;		//!< ��
	CatGameLib::LibSprite* titleLogo;	//!< �^�C�g�����S
	CatGameLib::LibSprite* titleStart;	//!< �Ђ炭���S
	CatGameLib::LibSprite* titleEnd;	//!< �Ƃ��郍�S

	CatGameLib::LibSprites* openBooks;	//!< �{���J��
	
	void playSound(void);
	void titleDraw(void);
	void select(void);
	void logoAnimation(void);
	void animation(void);
	void bookAnimation(void);
	void fadeout(void);
	void next(void);
};
}

#endif //!<  __MAGICAL_BOOK_TITLE_H__