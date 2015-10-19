
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

		void init(void) override;
		void update(void) override;

	private:

		CatGameLib::LibSprite*	floar;
		CatGameLib::LibSprites*	title_book;
		CatGameLib::LibSprite*	title_logo;
		CatGameLib::LibSprites*	player;
	};

}

#endif // __MAGICAL_BOOK_TITLE_H__