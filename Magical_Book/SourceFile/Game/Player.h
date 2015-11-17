
#ifndef __MAGICAL_BOOK_PLAYER_H__
#define __MAGICAL_BOOK_PLAYER_H__

#include "Character.h"

namespace MagicalBook 
{

class Player : public Character
{
public:
	void init(void);
	void update(Stage* stage);
	void draw(void);
	

	Player();
	~Player();

private:
	bool direction;
	int animationTimer;
	int animationCount;
	CatGameLib::LibSprites* sprites;
	CatGameLib::LibSprites* damageSprites;

	void move(Stage* stage);
};

}

#endif // __MAGICAL_BOOK_PLAYER_H__
