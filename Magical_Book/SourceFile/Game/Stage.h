
#ifndef __MAGICAL_BOOK_STAGE_H__
#define __MAGICAL_BOOK_STAGE_H__

#include "CatGameLib.h"
#include "ResourceManager.h"

namespace MagicalBook
{

class Stage
{
public:
	enum StageSize
	{
		Small	= 14,
		Medium	= 16,
		Large	= 18,
		SizeNum = 3,
	};

	Stage();
	~Stage();

	void update(void);
	void draw(void);

	void setBGNumber();
	void setMapData(const std::vector<unsigned char>& map);

	int getRotateCount(void);
	int getRotateDegree(void);
	float getRotateRadian(void);

	int getChipNumber(int x, int y);
	CatGameLib::LibVector2 getChipPosition(int x, int y);

private:
	int chipCount;
	int stageAngle;
	int rotateCount;
	
	ResourceManager::BgName bgNumber;
	ResourceManager::BgmNum musicNumber;

	CatGameLib::LibSprite*  bg;
	CatGameLib::LibSprite*  floor;
	CatGameLib::LibSprites* chip;
	CatGameLib::LibSprites* books;
	CatGameLib::LibSound*  bgm;
	CatGameLib::LibVector2 chipSize;
	CatGameLib::LibVector2 screenSize;
	CatGameLib::LibVector2 stageSize;
	CatGameLib::LibVector2 drawStartingPos;

	std::vector<unsigned char> stageData;
	std::vector<unsigned char> collisionData;
	std::vector<CatGameLib::LibVector2> chipPosition;
};

}

#endif // __MAGICAL_BOOK_STAGE_H__