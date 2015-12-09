
#ifndef __MAGICAL_BOOK_TITLE_H__
#define __MAGICAL_BOOK_TITLE_H__

#include "Scene.h"
#include "CatGameLib.h"


#define LOGO_MAX_SIZE 1.1f		//!< ロゴの最大サイズ
#define LOGO_MIN_SIZE 0.9f		//!< ロゴの最小サイズ
#define LOGO_ANIM_SPEED 3		//!< ロゴのアニメーション速度
#define LOGO_SIZE_ADD 0.01f		//!< ロゴのサイズ加算値

#define BOOK_MAX_SIZE 1.5f		//!< 本のサイズ
#define BOOK_SIZE_ADD 0.01f		//!< 本のサイズ加算度


namespace MagicalBook
{

class Title : public Scene
{
public:
	Title();
	~Title();

	void init(void) override;
	void update(void) override;


	enum TitleNumber
	{
		Select,		//!< 選択
		Animation,	//!< アニメーション
		Fadeout,	//!< フェードアウト
		Next,		//!< 次へ
	};
private:	
	
	float volume;		//!< 音量
	bool volumeFlag;	//!< 再生フラグ

	int timer;			//!< ロゴアニメーションタイマー
	float size;			//!< ロゴサイズ
	int logoFlag;		//!< ロゴフラグ
	float bookSize;		//!< 本サイズ
	int counter;		//!< カウンター
	bool flag;			//!< 処理の切り替え
	int animeNumber;	//!< アニメーション番号
	int titleWork;		//!< タイトルシーン
	
	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;		//!< 横画面中心
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;		//!< 縦画面中心

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* titleBgm;		//!< タイトルBGM
	CatGameLib::LibSound* menuSelect;	//!< 選択SE
	CatGameLib::LibSound* gameIn;		//!< 入るSE

	CatGameLib::LibSprite* fade;		//!< フェード
	CatGameLib::LibSprite* floor;		//!< 床
	CatGameLib::LibSprite* titleLogo;	//!< タイトルロゴ
	CatGameLib::LibSprite* titleStart;	//!< ひらくロゴ
	CatGameLib::LibSprite* titleEnd;	//!< とじるロゴ

	CatGameLib::LibSprites* openBooks;	//!< 本を開く
	
	void playSound(void);
	void titleDraw(void);
	void select(void);
	void logoAnimation(void);
	void animation(void);
	void bookAnimation(void);
	void fadeout(void);
	void next(void);
};
}

#endif //!<  __MAGICAL_BOOK_TITLE_H__