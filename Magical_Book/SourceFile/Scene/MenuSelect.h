
#ifndef __MAGICAL_BOOK_MENUSELECT_H__
#define __MAGICAL_BOOK_MENUSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"

#define LOGO_ANIM_SPEED 3
#define LOGO_MAX_SIZE 1.3f
#define LOGO_MIN_SIZE 0.8f
#define LOGO_SIZE_ADD 0.01f

#define BOOK_SIZE 1.5f
#define BOOK_SIZE_ADD 0.01f

namespace MagicalBook
{

class MenuSelect : public Scene
{
public:
	MenuSelect();
	~MenuSelect();

	void init(void) override;
	void update(void) override;

	enum MenuSelectNumber
	{
		Fadein,			//!< フェードイン
		ModeSelect,		//!< モード選択
		Animation,		//!< アニメーション
		Fadeout,		//!< フェードアウト
		Next,			//!< 次へ
	};

private:
	
	float volume;		//!< 音量
	bool volumeFlag;	//!< 再生フラグ

	int timer;			//!< ロゴアニメーションタイマー
	int logoFlag;		//!< ロゴフラグ
	int counter;		//!< カウンター
	bool flag;			//!< 処理の切り替え
	bool fadeFlag;		//!< フェード用フラグ
	int animeNumber;	//!< アニメーション番号
	int animeCounter;	//!< アニメーション用カウンター
	int selectWork;		//!< 選択シーン
	float size;			//!< ロゴサイズ

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< 横画面中心
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< 縦画面中心

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;	//!< モード選択画面BGM
	CatGameLib::LibSound* menuSelect;	//!< 選択SE

	CatGameLib::LibSprite* fade;		//!< フェード用
	CatGameLib::LibSprite* floor;		//!< 床
	CatGameLib::LibSprites* openBooks;	//!< 本を開く
	CatGameLib::LibSprites* books;		//!< 本をめくる
	CatGameLib::LibSprite* play;		//!< 遊ぶロゴ
	CatGameLib::LibSprite* make;		//!< 作るロゴ
	CatGameLib::LibSprite* back;		//!< 戻るロゴ

	void playSound(void);
	void menuSelectDraw(void);
	void fadein(void);
	void logoFadein(void);
	void modeSelect(void);
	void logoAnimation(void);
	void animation(void);
	void bookAnimation(void);
	void closeAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif //!<  __MAGICAL_BOOK_STSGESELECT_H__