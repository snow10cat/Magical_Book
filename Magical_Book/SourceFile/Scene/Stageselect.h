
#ifndef __MAGICAL_BOOK_STSGESELECT_H__
#define __MAGICAL_BOOK_STSGESELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class StageSelect : public Scene
{
public:
	StageSelect();
	~StageSelect();

	void init(void) override;
	void update(void) override;

	enum SelectNumber
	{
		GameMode,
		Back,
		Fadeout,
		Next,
	};

private:

	float volume;		//!< ¹Ê
	bool volumeFlag;	//!< Ä¶tO

	int timer;
	int counter;
	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int edit_select;
	int anime_number;
	int anime_counter;
	int select_work;
	float size;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* selectBgm;	//!< Xe[WIðæÊBGM
	CatGameLib::LibSound* menuSelect;	//!< IðSE

	CatGameLib::LibSprite* fade;		//!< tF[hp
	CatGameLib::LibSprite* floor;		//!< °
	CatGameLib::LibSprites* books;		//!< {ðß­é
	CatGameLib::LibSprite* frame;		//!< t[
	CatGameLib::LibSprite* arrow_right;	//!< Eîó
	CatGameLib::LibSprite* arrow_left;	//!< ¶îó
	CatGameLib::LibSprite* back;		//!< ßéS
	
	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< Xe[Wwi

	void playSound(void);
	void stageSelectDraw(void);
	void fadein(void);

	void modeSelect(void);
	void gameMode(void);
	void gameSelect(void);
	void gameModeDraw(void);
	void logoAnimation(void);
	void animation(void);
	void bookAnimation(void);
	void backAnimation(void);
	void closeAnimation(void);
	void fadeout(void);
	void next(void);
}

#endif // __MAGICAL_BOOK_STSGESELECT_H__