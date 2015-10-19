
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

		int counter;
		int title_work;

		enum TitleNumber
	{
		Init,
		Choose,
		Animation,
		Fadeout,
		Next,
	};
	private:

		CatGameLib::LibSprite*	floar;
		CatGameLib::LibSprites*	title_book;
		CatGameLib::LibSprite*	title_logo;
		CatGameLib::LibSprite*	title_start;
		CatGameLib::LibSprite*	title_end;
		CatGameLib::LibSprites*	player;
	};

}

#endif // __MAGICAL_BOOK_TITLE_H__