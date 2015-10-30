
#ifndef __MAGICAL_BOOK_GAME_H__
#define __MAGICAL_BOOK_GAME_H__

#include "CatGameLib.h"
#include "Scene.h"
#include "../Game/Character.h"
#include "../Game/Stage.h"

namespace MagicalBook
{

class Game : public Scene
{
public:
	Game();
	~Game();

	void init(void) override;
	void update(void) override;

private:
	std::vector<Character*> characters;
	Stage* stage;
};

}

#endif // __MAGICAL_BOOK_GAME_H__