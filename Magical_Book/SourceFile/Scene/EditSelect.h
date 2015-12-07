
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

	float volume;			//!< ‰¹—Ê
	bool volumeFlag;		//!< Ä¶ƒtƒ‰ƒO

	int sizeCounter;
	int bgCounter;
	int bgmCounter;
	int flag;
	int animeNumber;
	int animeCounter;

	int editSetWork;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< ‰¡‰æ–Ê’†S
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< c‰æ–Ê’†S

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;		//!< ƒXƒe[ƒW‘I‘ð‰æ–ÊBGM
	CatGameLib::LibSound* menuSelect;		//!< ‘I‘ðSE

	CatGameLib::LibSprite* floor;			//!< °
	CatGameLib::LibSprites* books;			//!< –{‚ð‚ß‚­‚é
	CatGameLib::LibSprite* sizeSection;		//!< ‘å‚«‚³ƒƒS
	CatGameLib::LibSprite* sizeLogo[3];		//!< S, M, LƒƒS
	CatGameLib::LibSprite* bgmLogos[3];		//!< BGMƒƒS
	CatGameLib::LibSprite* bgSection;		//!< ”wŒiƒƒS
	CatGameLib::LibSprite* musicSection;	//!< ‰¹ŠyƒƒS
	CatGameLib::LibSprite* frame;			//!< ƒtƒŒ[ƒ€
	CatGameLib::LibSprite* back;			//!< –ß‚éƒƒS

	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< ƒXƒe[ƒW”wŒi

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