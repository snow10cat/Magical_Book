
#ifndef __MAGICAL_BOOK_TITLE_H__
#define __MAGICAL_BOOK_TITLE_H__

#include "Scene.h"
#include "CatGameLib.h"

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
		Select,		//�I��
		Animation,	//�A�j���[�V����
		Fadeout,	//�t�F�[�h�A�E�g
		Next,		//����
	};
private:	
	
	float volume;		//����
	bool volumeFlag;	//�Đ��t���O

	int timer;			//���S�A�j���[�V�����^�C�}�[
	float size;			//���S�T�C�Y
	int counter;		//�J�E���^�[
	bool flag;			//�����̐؂�ւ�
	int animeNumber;	//�A�j���[�V�����ԍ�
	int titleWork;		//�^�C�g���V�[��
	
	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* titleBgm;		//�^�C�g��BGM
	CatGameLib::LibSound* menuSelect;	//�I��SE
	CatGameLib::LibSound* gameIn;		//����SE

	CatGameLib::LibSprite* fade;		//�t�F�[�h
	CatGameLib::LibSprite* floor;		//��
	CatGameLib::LibSprite* titleLogo;	//�^�C�g�����S
	CatGameLib::LibSprite* titleStart;	//�Ђ炭���S
	CatGameLib::LibSprite* titleEnd;	//�Ƃ��郍�S

	CatGameLib::LibSprites* openBooks;	//�{���J��
	
	void playSound(void);
	void titleDraw(void);
	void logoAnimation(void);
	void bookAnimation(void);

	void select(void);
	void animation(void);
	void fadeout(void);
	void next(void);
};
}

#endif // __MAGICAL_BOOK_TITLE_H__