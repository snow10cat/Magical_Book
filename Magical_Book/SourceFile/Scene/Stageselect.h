
#ifndef __MAGICAL_BOOK_STSGESELECT_H__
#define __MAGICAL_BOOK_STSGESELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class StageSelect : public Scene
{
public:
	StageSelect();
	~StageSelect();

	void init(void) override;
	void update(void) override;

	enum SelectNumber
	{
		GameMode,
		Back,
		Fadeout,
		Next,
	};

private:

	float volume;		//!< 音量
	bool volumeFlag;	//!< 再生フラグ

	int timer;
	int counter;
	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int edit_select;
	int anime_number;
	int anime_counter;
	int select_work;
	float size;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* selectBgm;	//!< ステージ選択画面BGM
	CatGameLib::LibSound* menuSelect;	//!< 選択SE

	CatGameLib::LibSprite* fade;		//!< フェード用
	CatGameLib::LibSprite* floor;		//!< 床
	CatGameLib::LibSprites* books;		//!< 本をめくる
	CatGameLib::LibSprite* frame;		//!< フレーム
	CatGameLib::LibSprite* arrow_right;	//!< 右矢印
	CatGameLib::LibSprite* arrow_left;	//!< 左矢印
	CatGameLib::LibSprite* back;		//!< 戻るロゴ
	
	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< ステージ背景

	void playSound(void);
	void stageSelectDraw(void);
	void fadein(void);

	void modeSelect(void);
	void gameMode(void);
	void gameSelect(void);
	void gameModeDraw(void);
	void logoAnimation(void);
	void animation(void);
	void bookAnimation(void);
	void backAnimation(void);
	void closeAnimation(void);
	void fadeout(void);
	void next(void);
}

#endif // __MAGICAL_BOOK_STSGESELECT_H__