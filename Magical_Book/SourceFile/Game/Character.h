
#ifndef __MAGICAL_BOOK_CHARACTER_H__
#define __MAGICAL_BOOK_CHARACTER_H__

#include "CatGameLib.h"
#include "Stage.h"

namespace MagicalBook
{

class Character
{
public:
	virtual void init(void) = 0;
	virtual void update(Stage* stage) = 0;
	virtual void draw(void) = 0;

	CatGameLib::LibVector2 getPosition( void);

protected:
	enum CharacterState
	{
		Idle,
		NoMove,
		Walk,
		Fall,
		Door,
		Damage,
	};

	CharacterState state;
	CatGameLib::LibVector2 velocity;
	CatGameLib::LibVector2 position;

	void rotation( int angle);
	virtual void move( Stage* stage) = 0;
};

}

#endif // __MAGICAL_BOOK_CHARACTER_H__