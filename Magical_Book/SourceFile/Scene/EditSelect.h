
#ifndef __MAGICAL_BOOK_EDITSELECT_H__
#define __MAGICAL_BOOK_EDITSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class EditSelect : public Scene
{
public:
	EditSelect ();
	~EditSelect ();

	void init(void) override;
	void update(void) override;

	enum EditSelectNumber
	{
		logoFadein,
		EditMenuSelect,
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

	int sizeCounter;
	int bgCounter;
	int bgmCounter;
	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int anime_number;
	int anime_counter;
	int editMode_work;
	float Volume;
	int volumeFlag;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	CatGameLib::LibSprites* books;

	CatGameLib::LibSprite* size_section;
	CatGameLib::LibSprite* bg_section;
	CatGameLib::LibSprite* music_section;
	CatGameLib::LibSprite* bgm_logo[3];
	CatGameLib::LibSprite* size_logo[3];

	std::vector<CatGameLib::LibSprite*> bgTextures;

	void logoFade(void);
	void bookAnimation(void);
	void playSound(void);

	void sizeSelect(void);
	void bgSelect(void);
	void bgmSelect(void);
	void animation(void);
	void editSetUp(void);
	void editSetUpDraw(void);
	void backAnimation(void);
	void closeAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__