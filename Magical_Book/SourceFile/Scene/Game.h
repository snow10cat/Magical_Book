
#ifndef __MAGICAL_BOOK_GAME_H__
#define __MAGICAL_BOOK_GAME_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class Game : public Scene
{
public:
	Game();
	~Game();

	void init( void) override;
	void update( void) override;

private:
	CatGameLib::LibSprites* books;
	CatGameLib::LibSprite* fox;
	CatGameLib::LibSprite* fox2;
};

}

#endif // __MAGICAL_BOOK_GAME_H__