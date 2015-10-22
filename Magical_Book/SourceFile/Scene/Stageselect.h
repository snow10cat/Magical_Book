
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
		Fadeout,
		Next,
	};

private:

	int counter;
	int flag;
	int anime_number;
	int select_work;
	float size;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSprite* frame;
	CatGameLib::LibSprite* play;
	CatGameLib::LibSprite* make;
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__