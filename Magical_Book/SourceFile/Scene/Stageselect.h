
#ifndef __MAGICAL_BOOK_STSGESELECT_H__
#define __MAGICAL_BOOK_STSGESELECT_H__

#include "Scene.h"
#include "CatGameLib.h"


#define SELECT_SIZE 0.35f 		//!< 選択時サイズ
#define DESELECT_SIZE 0.3f		//!< 非選択時サイズ
#define SELECT_ARROW_SIZE 0.1f	//!< 矢印の選択時サイズ
#define SELECT_BACK_SIZE 1.2f	//!< 戻るロゴの選択時サイズ

#define FRAME_SIZE_X 0.35f		//!< 戻るロゴ選択時のフレームXサイズ
#define FRAME_SIZE_Y 0.12f		//!< 戻るロゴ選択時のフレームYサイズ

#define BOOK_SIZE 1.5f	  		//!< 本のサイズ
#define BOOK_SIZE_ADD 0.1f		//!< 本のサイズ加算度


namespace MagicalBook
{

class StageSelect : public Scene
{
public:
	StageSelect();
	~StageSelect();

	void init(void) override;
	void update(void) override;

	enum StageSelectNumber
	{
		SelectStage,		//!< ステージ選択
		BackAnimation,		//!< 前に戻るアニメーション
		Animation,			//!< アニメーション
		Next,				//!< 次へ
	};

private:

	enum SelectPosition
	{
		LeftUp,			//!< 左上
		RightUp,		//!< 右上
		LeftDown,		//!< 左下
		RightDown,		//!< 右下
		Leftarrow,		//!< 左矢印
		Rightarrow,		//!< 右矢印
		BackLogo,		//!< 戻るロゴ
	};
	
	float volume;			//!< 音量
	bool volumeFlag;		//!< 再生フラグ

	int selectFlag;			//!< 選択フラグ

	int counter;			//!< カウンター
	int animeNumber;		//!< アニメーション番号
	int animeCounter;		//!< アニメーション用カウンター
	int stageSelectWork;	//!< 選択シーン

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< 横画面中心
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< 縦画面中心

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* selectBgm;	//!< ステージ選択画面BGM
	CatGameLib::LibSound* menuSelect;	//!< 選択SE

	CatGameLib::LibSprite* fade;		//!< フェード用
	CatGameLib::LibSprite* floor;		//!< 床
	CatGameLib::LibSprites* books;		//!< 本をめくる
	CatGameLib::LibSprite* arrowRight;	//!< 右矢印
	CatGameLib::LibSprite* arrowLeft;	//!< 左矢印
	CatGameLib::LibSprite* frame;		//!< フレーム
	CatGameLib::LibSprite* back;		//!< 戻るロゴ
	
	std::vector<CatGameLib::LibSprite*> bgTextures;		//!< ステージ背景

	void playSound(void);
	void stageSelectDraw(void);
	void logoFadein(void);
	void bgFadein(void);
	void stageSelect(void);
	void selectActions(void);
	void changeSize(void);
	void backAnimation(void);
	void bookAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__