
#ifndef __MAGICAL_BOOK_EDIT_H__
#define __MAGICAL_BOOK_EDIT_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class Edit : public Scene
{
public:
	Edit ();
	~Edit ();

	void init(void) override;
	void update(void) override;

	enum EditNumber
	{
		Fadein,
		EditSelect,
		Animation,
		Back,
		Next,
	};

	enum EditMenu
	{
		StageSize,
		StageBG,
		StageBGM,
	};

private:

	int chipCounter;

	int sizeCounter;
	int bgCounter;
	int bgmCounter;

	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int anime_number;
	int anime_counter;
	int edit_work;
	float Volume;
	int volumeFlag;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* edit_bgm;
	
	CatGameLib::LibSprite* material_logo;
	CatGameLib::LibSprite* chipTable;

	CatGameLib::LibSprite* grid_size[3];
	CatGameLib::LibSprite* music_num[3];

	CatGameLib::LibSprites* chip;
	CatGameLib::LibSprites* player;
	CatGameLib::LibSprites* enemy;
	CatGameLib::LibSprites* gimmick;
	CatGameLib::LibSprites* door;
	
	std::vector<CatGameLib::LibVector2> chipPosition;
	std::vector<CatGameLib::LibSprite*> bgTextures;

	void pictFade(void);
	void bookAnimation(void);
	void playSound(void);

	void sizeSelect(void);
	void bgSelect(void);
	void bgmSelect(void);
	void animation(void);
	void edit(void);
	void editDraw(void);
	void backAnimation(void);
	void closeAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif //__MAGICAL_BOOK_EDIT_H__