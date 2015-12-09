
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
	
	enum StageSize
	{
		Small	= 14,		//!< Sサイズ(マップチップ14個分)
		Medium	= 16,		//!< Mサイズ(マップチップ16個分)
		Large	= 18,		//!< Lサイズ(マップチップ18個分)
		SizeNum = 3,		
	};

	enum EditSelect
	{
		MaterialSelect,
		MaterialSet,
	};

private:
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

	float Volume;
	int volumeFlag;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;

	CatGameLib::LibSound* edit_bgm;
	
	CatGameLib::LibSprite* material_logo;
	CatGameLib::LibSprite* chipTable;
	CatGameLib::LibSprite* save;
	CatGameLib::LibSprite* redo;
	CatGameLib::LibSprite* undo;
	CatGameLib::LibSprite* pointer;
	CatGameLib::LibSprite* back;

	CatGameLib::LibSprite* grid_size[3];
	CatGameLib::LibSprite* music_num[3];
	
	CatGameLib::LibSprites* books;
	CatGameLib::LibSprites* chip;
	CatGameLib::LibSprites* player;
	CatGameLib::LibSprites* enemy;
	CatGameLib::LibSprites* gimmick;
	CatGameLib::LibSprites* door;
	
	CatGameLib::LibSprites* materialPlayer;
	CatGameLib::LibSprites* materialEnemy;
	CatGameLib::LibSprites* materialGimmick;
	CatGameLib::LibSprites* materialDoor;
	
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
	void editChipSetDraw(void);
	
	void backAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif //__MAGICAL_BOOK_EDIT_H__