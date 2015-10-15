
#ifndef __MAGICAL_BOOK_TITLE_H__
#define __MAGICAL_BOOK_TITLE_H__

#include "Scene.h"
#include "../CatGameLib/LibSprite.h"

namespace MagicalBook
{

class Title : public Scene
{
public:
	Title();
	~Title();

	void init( void) override;
	void update( void) override;

private:
	CatGameLib::LibSprite* test;
	CatGameLib::LibSprite* fox;
	CatGameLib::LibSprite* fox2;
};

}

#endif // __MAGICAL_BOOK_TITLE_H__