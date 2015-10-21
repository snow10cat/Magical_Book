
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

	void init( void) override;
	void update( void) override;

private:

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibSprites* books;
	CatGameLib::LibSprite* fox;
	CatGameLib::LibSprite* fox2;
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__