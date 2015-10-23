
#ifndef __MAGICAL_BOOK_STSGESELECT_H__
#define __MAGICAL_BOOK_STSGESELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class Stageselect : public Scene
{
public:
	Stageselect();
	~Stageselect();

	void init(void) override;
	void update(void) override;

	enum SelectNumber
	{
		ModeSelect,
		Animation,
		GameMode,
		EditMode,
		Back,
		Fadeout,
		Next,
	};

	enum EditSelect
	{
		StageSize,
		StageBG,
		StageBGM,
	};

private:

	int timer;
	int counter;
	int flag;
	int edit_select;
	int anime_number;
	int anime_counter;
	int select_work;
	float size;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	CatGameLib::LibSprites* books;

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
	void gameModeDraw(void);
	void editMode(void);
	void editModeDraw(void);
	void backAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__