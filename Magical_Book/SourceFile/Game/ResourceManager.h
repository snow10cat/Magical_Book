
#ifndef __MAGICAL_BOOK_RESOURCE_MANEGER_H__
#define __MAGICAL_BOOK_RESOURCE_MANEGER_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace MagicalBook
{

class ResourceManager
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

	enum BgmNum
	{
		BGM_1,
		BGM_2,
		BGM_3,
		BGM_Count = BGM_3 + 1,
	};

	static ResourceManager* getInstance(void)
	{
		static ResourceManager* instance = nullptr;
		if(!instance) {instance = new ResourceManager();}
		return instance;
	}
	ResourceManager(const ResourceManager&) = delete;
	const ResourceManager& operator=(const ResourceManager&) = delete;

	void loadResource( void);

	CatGameLib::LibSound* getSound(const std::string& fileName);

	CatGameLib::LibSprite* getSprite(const std::string& fileName);
	CatGameLib::LibSprites* getSprites(const std::string& fileName);

private:

	ResourceManager();
	~ResourceManager();

	std::map<std::string, CatGameLib::LibSound*> soundArray;

	std::map<std::string, CatGameLib::LibSprite*> spriteArray;
	std::map<std::string, CatGameLib::LibSprites*> spritesArray;
};

}

#endif // __MAGICAL_BOOK_SPRITE_MANEGER_H__


