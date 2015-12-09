
#ifndef __MAGICAL_BOOK_RESOURCE_MANEGER_H__
#define __MAGICAL_BOOK_RESOURCE_MANEGER_H__

#include "CatGameLib.h"
#include "ExternalLib.h"


#define MAX_VOLUME 1.0f			//!< 最大音量
#define BGM_FADE 0.02f			//!< 音楽フェード加算値
#define DEFAULT_SIZE 1.0f		//!< 初期サイズ
#define FADE 10					//!< フェード加算値

#define BOOK_POS_X 300			//!< 画面中心から位置調整した値(開いている本の位置)
#define TITLE_BOOK_POS_X 250	//!< 画面中心から位置調整した値(タイトルの本位置)
#define EDIT_SEL_BOOK_POS_X 320	//!< 画面中心から位置調整した値(エディット選択の本位置)
#define EDIT_BOOK_POS_X 200		//!< 画面中心から位置調整した値(エディットの本位置)
#define MOVEMENT_BOOK 10		//!< 本の移動速度
#define BOOK_ANIM_SPEED 7		//!< 本のアニメーション速度


namespace MagicalBook
{

class ResourceManager
{
public:
	enum Size
	{
		Size_S,						//!< Sサイズ
		Size_M,						//!< Mサイズ
		Size_L,						//!< Lサイズ
		Size_Count = Size_L + 1,	//!< サイズの数
	};

	enum BgName
	{
		BG_Castle,					//!< 背景(城前)
		BG_Table,					//!< 背景(机)
		BG_Gate,					//!< 背景(門)
		BG_Window,					//!< 背景(窓)
		BG_Throne,					//!< 背景(玉座)
		BG_Count = BG_Throne + 1,	//!< 背景の数
	};

	enum BgmNum
	{
		BGM_1,						//!< 音楽1
		BGM_2,						//!< 音楽2
		BGM_3,						//!< 音楽3
		BGM_Count = BGM_3 + 1,		//!< 音楽の数
	};

	static ResourceManager* getInstance(void)
	{
		static ResourceManager* instance = nullptr;
		if(!instance) {instance = new ResourceManager();}
		return instance;
	}
	ResourceManager(const ResourceManager&) = delete;

	const ResourceManager& operator=(const ResourceManager&) = delete;

	void loadResource(void);

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


