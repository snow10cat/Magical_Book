
#ifndef __MAGICAL_BOOK_EDITSELECT_H__
#define __MAGICAL_BOOK_EDITSELECT_H__

#include "Scene.h"
#include "CatGameLib.h"


#define LOGO_SIZE 0.7f			//!< ロゴサイズ
#define SELECT_LOGO_SIZE 0.8f	//!< 選択ロゴサイズ
#define SELECT_BACK_SIZE 1.2f	//!< 戻るロゴの選択時サイズ

#define SELECT_SIZE 0.35f 		//!< 選択時の大きさ、音楽サイズ
#define DESELECT_SIZE 0.25f		//!< 非選択時の大きさ、音楽サイズ

#define SELECT_BG_SIZE 0.2f		//!< 選択時の背景サイズ
#define DESELECT_BG_SIZE 0.1f	//!< 非選択時の背景サイズ

#define FRAME_SIZE 0.15f		//!< フレームサイズ
#define BG_FRAME_SIZE 0.2f		//!< 背景用フレームサイズ
#define FRAME_SIZE_X 0.3f		//!< 戻るロゴ選択時のフレームXサイズ
#define FRAME_SIZE_Y 0.1f		//!< 戻るロゴ選択時のフレームYサイズ

#define BOOK_SIZE 1.5f			//!< 本のサイズ

#define BACK 0					//!< 戻る


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
		Fadein,				//!< フェードイン
		EditMenuSelect,		//!< エディットメニュー選択
		BackAnimation,		//!< 前に戻るアニメーション
		Animation,			//!< 次に行くアニメーション
		Next,				//!< 次へ
	};
private:

	enum EditMenu
	{
		StageSize,			//!< サイズ選択
		StageBG,			//!< 背景選択
		StageBGM,			//!< 音楽選択
	};
	
	enum EditSize
	{
		//0はBACK
		Size_S = 1,			//!< Sサイズ
		Size_M,				//!< Mサイズ
		Size_L,				//!< Lサイズ
		Size_Count			//!< 大きさの数 + 1(BACKの分)
	};

	enum EditBg
	{
		//0はBACK
		BG_Castle = 1,		//!< 背景(城前)
		BG_Table,			//!< 背景(机)
		BG_Gate,			//!< 背景(門)
		BG_Window,			//!< 背景(窓)
		BG_Throne,			//!< 背景(玉座)
		BG_Count			//!< 背景の数 + 1(BACKの分)
	};

	enum EditBgm
	{
		//0はBACK
		Bgm_1 = 1,			//!< 音楽1
		Bgm_2,				//!< 音楽2
		Bgm_3,				//!< 音楽3
		Bgm_Count			//!< 音楽の数 + 1(BACKの分)
	};

	float volume;			//!< 音量
	bool volumeFlag;		//!< 再生フラグ
	int bgmCount;			//!< BGMカウント

	int setUpWork;			//!< 設定シーン
	int sizeCounter;		//!< 大きさのカウンター
	int bgCounter;			//!< 背景のカウンター 
	int bgmCounter;			//!< 音楽のカウンター
	int animeNumber;		//!< アニメーション番号
	int animeCounter;		//!< アニメーション用カウンター

	int editSetWork;		//!< エディット選択シーン

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< 横画面中心
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< 縦画面中心

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* selectBgm;		//!< ステージ選択画面BGM
	CatGameLib::LibSound* stageBgm[3];		//!< ステージBGM
	CatGameLib::LibSound* menuSelect;		//!< 選択SE

	CatGameLib::LibSprite* floor;			//!< 床
	CatGameLib::LibSprites* books;			//!< 本をめくる
	CatGameLib::LibSprite* sizeSection;		//!< 大きさロゴ
	CatGameLib::LibSprite* sizeLogo[3];		//!< S, M, Lロゴ
	CatGameLib::LibSprite* bgmLogos[3];		//!< BGMロゴ
	CatGameLib::LibSprite* bgSection;		//!< 背景ロゴ
	CatGameLib::LibSprite* musicSection;	//!< 音楽ロゴ
	CatGameLib::LibSprite* frame;			//!< フレーム
	CatGameLib::LibSprite* back;			//!< 戻るロゴ

	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< ステージ背景

	void playSound(void);
	void editSetUpDraw(void);
	void logoFadein(void);
	void editSetUp(void);
	void sizeSelect(void);
	void bgSelect(void);
	void bgmSelect(void);
	void backAnimation(void);
	void bookAnimation(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__