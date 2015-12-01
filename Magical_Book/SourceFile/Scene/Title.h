
#ifndef __MAGICAL_BOOK_TITLE_H__
#define __MAGICAL_BOOK_TITLE_H__

#include "Scene.h"
#include "CatGameLib.h"

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
		Select,		//選択
		Animation,	//アニメーション
		Fadeout,	//フェードアウト
		Next,		//次へ
	};
private:	
	
	float volume;		//音量
	bool volumeFlag;	//再生フラグ

	int timer;			//ロゴアニメーションタイマー
	float size;			//ロゴサイズ
	int counter;		//カウンター
	bool flag;			//処理の切り替え
	int animeNumber;	//アニメーション番号
	int titleWork;		//タイトルシーン
	
	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* titleBgm;		//タイトルBGM
	CatGameLib::LibSound* menuSelect;	//選択SE
	CatGameLib::LibSound* gameIn;		//入るSE

	CatGameLib::LibSprite* fade;		//フェード
	CatGameLib::LibSprite* floor;		//床
	CatGameLib::LibSprite* titleLogo;	//タイトルロゴ
	CatGameLib::LibSprite* titleStart;	//ひらくロゴ
	CatGameLib::LibSprite* titleEnd;	//とじるロゴ

	CatGameLib::LibSprites* openBooks;	//本を開く
	
	void playSound(void);
	void titleDraw(void);
	void logoAnimation(void);
	void bookAnimation(void);

	void select(void);
	void animation(void);
	void fadeout(void);
	void next(void);
};
}

#endif // __MAGICAL_BOOK_TITLE_H__