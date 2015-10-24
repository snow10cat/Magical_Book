
#ifndef __MAGICAL_BOOK_STAGE_H__
#define __MAGICAL_BOOK_STAGE_H__

#include "CatGameLib.h"

namespace MagicalBook
{

class Stage
{
public:
	enum StageSize
	{
		Small,
		Medium,
		Large,
		SizeNum,
	};

	Stage();
	~Stage();

	void update(void);
	void draw(void);

	int getRotateDegree( void);
	float getRotateRadian( void);

	int getChipNumbr( int x, int y);

private:
	int stageWidth;
	int stageHeight;
	int stageSize;
	int rotateCount;
	int stageAngle;

	CatGameLib::LibSprites* chip;
	CatGameLib::LibVector2 chipSize;
	CatGameLib::LibVector2 screenSize;
	std::vector<CatGameLib::LibVector2> chipPosition;
};

}

#endif // __MAGICAL_BOOK_STAGE_H__