
#ifndef __MAGICAL_BOOK_EDITSELECT_H__
#define __MAGICAL_BOOK_EDITSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

#define BACK 0

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
		Fadein,
		EditMenuSelect,
		BackAnimation,
		Animation,
		Next,
	};

	enum EditMenu
	{
		StageSize,
		StageBG,
		StageBGM,
	};

private:

	enum EditSize
	{
		Size_S = 1,
		Size_M,
		Size_L,
	};

	enum EditBg
	{
		BG_Castle = 1,
		BG_Table,
		BG_Gate,
		BG_Window,
		BG_Throne,
	};

	enum EditBgm
	{
		Bgm_1 = 1,
		Bgm_2,
		Bgm_3,
	};

	float volume;			//!< ����
	bool volumeFlag;		//!< �Đ��t���O

	int sizeCounter;
	int bgCounter;
	int bgmCounter;
	int flag;
	int animeNumber;
	int animeCounter;

	int editSetWork;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< ����ʒ��S
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< �c��ʒ��S

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;		//!< �X�e�[�W�I�����BGM
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