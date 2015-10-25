
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

	void setBGNumber( );
	void setMapData( const std::vector<unsigned char>& map);

	int getRotateDegree( void);
	float getRotateRadian( void);

	int getChipNumbr( int x, int y);

private:
	int chipCount;
	int stageAngle;
	int rotateCount;
	
	CatGameLib::LibSprites* chip;
	CatGameLib::LibVector2 chipSize;
	CatGameLib::LibVector2 screenSize;
	CatGameLib::LibVector2 stageSize;
	CatGameLib::LibVector2 drawStartingPos;
	std::vector<CatGameLib::LibVector2> chipPosition;
};

}

#endif // __MAGICAL_BOOK_STAGE_H__