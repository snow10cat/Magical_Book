
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
		Fadein,			//!< フェードイン
		EditSet,		//!< エディットモード
		BackAnimation,	//!< 前に戻るアニメーション
		Animation,		//!< 次に行くアニメーション
		Next,			//!< 次へ
	};
	
	

private:

	enum StageSize
	{
		Small	= 14,		//!< Sサイズ(マップチップ14個分)
		Medium	= 16,		//!< Mサイズ(マップチップ16個分)
		Large	= 18,		//!< Lサイズ(マップチップ18個分)
		SizeNum = 3,		
	};

	enum MaterialNum
	{
		Chip,
		Player,
		Enemy,
		Door,
		Gimmick,
		MaterialCount,
	};

	enum EditSelect
	{
		MaterialSelect,
		MaterialSet,
	};

	float volume;		//!< 音量
	int volumeFlag;		//!< 再生フラグ

	int chipCount;
	int chipNum;
	int chipState;
	int chipCounter;
	int chipDirection;
	int chipHave;

	int sizeCounter;
	int bgCounter;
	int bgmCounter;

	int counter;

	int materialRow;		//行
	int materialCol;		//列
	
	int materialSetRow;		//行
	int materialSetCol;		//列

	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int anime_number;
	int anime_counter;

	int edit_work;
	int edit_set_work;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* editBgm;

	CatGameLib::LibSprite* floor;				//!< 床
	CatGameLib::LibSprites* books;				//!< 本
	
	CatGameLib::LibSprite* materialLogo;		//!< 素材ロゴ
	CatGameLib::LibSprite* chipTable;			//!< 素材を置くフレーム
	CatGameLib::LibSprite* save;				//!< 保存
	CatGameLib::LibSprite* redo;				//!< 1つ進む
	CatGameLib::LibSprite* undo;				//!< 1つ戻る
	CatGameLib::LibSprite* pointer;				//!< カーソル
	CatGameLib::LibSprite* back;				//!< 戻るロゴ

	CatGameLib::LibSprites* materials[5];		//!< 素材

	CatGameLib::LibSprite* gridSize[3];			//!< グリッド線
	
	CatGameLib::LibSprites* setMaterials[5];	//!< 配置した素材

	CatGameLib::LibSprites* chip;/*
	CatGameLib::LibSprites* player;
	CatGameLib::LibSprites* enemy;
	CatGameLib::LibSprites* gimmick;
	CatGameLib::LibSprites* door;*/
	CatGameLib::LibSprite* music_num[3];
	
	CatGameLib::LibVector2 chipSize;
	CatGameLib::LibVector2 screenSize;
	CatGameLib::LibVector2 stageSize;
	CatGameLib::LibVector2 drawStartingPos;

	std::vector<CatGameLib::LibVector2> chipPosition;
	std::vector<CatGameLib::LibSprite*> bgTextures;

	void pictFade(void);
	void bookAnimation(void);
	void playSound(void);

	void animation(void);
	void edit(void);
	
	void materialSelect(void);
	void materialSet(void);
	
	void editDraw(void);
	void materialDraw(void);
	void editChipSetDraw(void);
	
	void backAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif //__MAGICAL_BOOK_EDIT_H__