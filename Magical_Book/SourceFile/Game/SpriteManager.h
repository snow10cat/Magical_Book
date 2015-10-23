
#ifndef __MAGICAL_BOOK_SPRITE_MANEGER_H__
#define __MAGICAL_BOOK_SPRITE_MANEGER_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace MagicalBook
{

class SpriteManager
{
public:

	enum BgName
	{
		BG_Castle,
		BG_Table,
		BG_Gate,
		BG_Window,
		BG_Throne,
		BG_Count = BG_Throne + 1,
	};

	/**
	 * ライブラリインスタンス取得
	 *
	 * @author	minaka1412
	 * @return  インスタンスへのポインタ
	 */
	static SpriteManager* getInstance(void)
	{
		static SpriteManager* instance = nullptr;
		if(!instance) {instance = new SpriteManager();}
		return instance;
	}
	SpriteManager(const SpriteManager&) = delete;
	const SpriteManager& operator=(const SpriteManager&) = delete;

	void loadSprite( void);

	CatGameLib::LibSprite* getSprite(const std::string& fileName);
	CatGameLib::LibSprites* getSprites(const std::string& fileName);

private:

	SpriteManager();
	~SpriteManager();
	std::map<std::string, CatGameLib::LibSprite*> spriteArray;
	std::map<std::string, CatGameLib::LibSprites*> spritesArray;
};

}

#endif // __MAGICAL_BOOK_SPRITE_MANEGER_H__


