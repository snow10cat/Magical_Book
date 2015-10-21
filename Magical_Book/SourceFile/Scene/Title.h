
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
		Select,
		Animation,
		Fadeout,
		Next,
	};
private:	

	int counter;
	int flag;
	int anime_number;
	int title_work;
	float size;
	
	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* title_bgm;
	CatGameLib::LibSound* select_se;
	CatGameLib::LibSound* game_in;

	CatGameLib::LibSprite* floar;
	CatGameLib::LibSprite* fadeout;
	CatGameLib::LibSprites*	title_book;
	CatGameLib::LibSprite* title_logo;
	CatGameLib::LibSprite* title_start;
	CatGameLib::LibSprite* title_end;
};
}

#endif // __MAGICAL_BOOK_TITLE_H__