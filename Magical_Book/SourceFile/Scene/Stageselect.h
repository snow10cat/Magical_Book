
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

	enum StageSelectNumber
	{
		SelectStage,		//!< ステージ選択
		BackAnimation,		//!< 前に戻るアニメーション
		Animation,			//!< アニメーション
		Next,				//!< 次へ
	};

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

private:

	float volume;			//!< 音量
	bool volumeFlag;		//!< 再生フラグ

	int selectFlag;			//!< 選択フラグ

	int counter;			//!< カウンター
	int animeNumber;		//!< アニメーション番号
	int animeCounter;		//!< アニメーション用カウンター
	int stageSelectWork;	//!< 選択シーン

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

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

	void cangeSize(void);
	void backAnimation(void);
	void bookAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif // __MAGICAL_BOOK_STSGESELECT_H__