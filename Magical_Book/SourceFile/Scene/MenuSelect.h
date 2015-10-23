
#ifndef __MAGICAL_BOOK_MENUSELECT_H__
#define __MAGICAL_BOOK_MENUSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

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
		Fadein,
		ModeSelect,
		Animation,
		Back,
		Fadeout,
		Next,
	};

private:

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
	float Volume;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	CatGameLib::LibSprites* books;

	CatGameLib::LibSound* select_bgm;

	CatGameLib::LibSprite* frame;
	CatGameLib::LibSprite* play;
	CatGameLib::LibSprite* make;
	CatGameLib::LibSprite* back;
	CatGameLib::LibSprite* arrow_right;
	CatGameLib::LibSprite* arrow_left;

	std::vector<CatGameLib::LibSprite*> bgTextures;

	void logoAnimation(void);
	void bookAnimation(void);

	void modeSelect(void);
	void animation(void);
	void gameMode(void);
	void gameSelect(void);
	void gameModeDraw(void);
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