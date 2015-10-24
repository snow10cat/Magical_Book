
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
		ModeSelect,
		Animation,
		GameMode,
		EditMode,
		Back,
		Fadeout,
		Next,
	};

	/*enum EditSelect
	{
		StageSize,
		StageBG,
		StageBGM,
	};*/

private:

	int timer;
	int counter;
	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int edit_select;
	int anime_number;
	int anime_counter;
	int editMode_work;
	float Volume;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	CatGameLib::LibSprites* books;

	CatGameLib::LibSound* select_bgm;

	CatGameLib::LibSprite* size_section;
	CatGameLib::LibSprite* bg_section;
	CatGameLib::LibSprite* music_section;
	CatGameLib::LibSprite* bgm_logo[3];
	CatGameLib::LibSprite* size_logo[3];

	CatGameLib::LibSprite* arrow_right;
	CatGameLib::LibSprite* arrow_left;

	std::vector<CatGameLib::LibSprite*> bgTextures;

	void logoAnimation(void);
	void bookAnimation(void);

	void modeSelect(void);
	void animation(void);
	void editMode(void);
	void editModeDraw(void);
	void backAnimation(void);
	void closeAnimation(void);
	void fadein(void);
	void fadeout(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__