
#ifndef __MAGICAL_BOOK_EDITSELECT_H__
#define __MAGICAL_BOOK_EDITSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

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

	float volume;			//!< ¹Ê
	bool volumeFlag;		//!< Ä¶tO

	int sizeCounter;
	int bgCounter;
	int bgmCounter;
	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int anime_number;
	int anime_counter;

	int editSetWork;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;		//!< Xe[WIðæÊBGM
	CatGameLib::LibSound* menuSelect;		//!< IðSE

	CatGameLib::LibSprite* floor;			//!< °
	CatGameLib::LibSprites* books;			//!< {ðß­é
	CatGameLib::LibSprite* sizeSection;		//!< å«³S
	CatGameLib::LibSprite* sizeLogo[3];		//!< S, M, LS
	CatGameLib::LibSprite* bgmLogos[3];		//!< BGMS
	CatGameLib::LibSprite* bgSection;		//!< wiS
	CatGameLib::LibSprite* musicSection;	//!< ¹yS
	CatGameLib::LibSprite* frame;			//!< t[
	CatGameLib::LibSprite* back;			//!< ßéS

	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< Xe[Wwi

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