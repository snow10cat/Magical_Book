
#include "ResourceManager.h"
#include "CatGameLib.h"
#include "Stage.h"

#include <algorithm>

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

vector<int> stageData = {
	29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,
	29,-1,-1,-1,-1,-1,-1,29,-1,-1,-1,-1, 0,-1,-1,29,
	29,-1,-1,-1, 0,-1,-1,29,-1,-1,-1,29,29,-1,-1,29,
	29,-1,-1,-1,29,-1,-1,29,-1,-1,-1,29,-1,-1,-1,29,
	29,-1,-1,-1,29,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,29,
	29,-1,-1,-1,29,29,29,29,29,29,-1,-1,-1,-1,-1,29,
	29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,
	29,29,29,-1,-1,-1,-1,-1,-1,-1,-1, 0,29,29,29,29,
	29,-1,-1,-1,-1,-1,-1,-1,29,29,-1,-1,29,-1,-1,29,
	29,-1,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,
	29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,
	29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,
	29,29,29,-1,-1,29,29,29,-1,-1,29,29,-1,29,29,29,
	29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,
	29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0,29,
	29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,
};

vector<int> collisionData;

const static int stageChipCount[] = { 14, 16, 18 };

Stage::Stage() : chipCount( 0),
				 stageAngle( 0),
				 rotateCount( 0)
{
	chip = ResourceManager::getInstance() -> getSprites("mapchip");
	screenSize = LibMain::getInstance() -> getScreenSize();
	chipSize = chip -> getTextureSizeX();

	collisionData = stageData;

	/*
		ここでステージデータ読み込み
	*/

	stageSize.x = 16;
	stageSize.y = 16;

	drawStartingPos.x = (screenSize.x / 2) - ( (stageSize.x / 2) * chipSize.x) + chipSize.x * chip -> getAnchorPointX();
	drawStartingPos.y = (screenSize.y / 2) - ( (stageSize.y / 2) * chipSize.y) + chipSize.y * chip -> getAnchorPointY();

	chipCount = stageSize.x * stageSize.y;

	chipPosition.resize( chipCount);

	for( int y = 0; y < stageSize.y; y++)
	{
		for( int x = 0, posX = stageSize.x - 1; x < stageSize.x; x++, posX--)
		{
			const int arrayNumber = y * stageSize.x + x;
			chipPosition[arrayNumber].x = drawStartingPos.x + posX * chipSize.x;
			chipPosition[arrayNumber].y = drawStartingPos.y + y * chipSize.y;
		}
	}
}

Stage::~Stage()
{
}

void Stage::update(void)
{
	LibCircle angle = 0;
	LibInput* input = LibInput::getInstance();

	if( input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_F))
	{
		rotateCount--;
		vector<int> buffer = collisionData;
		for( int y = 0; y < stageSize.y; y++)
		{
			for( int x = 0; x < stageSize.x; x++)
			{
				int i = stageSize.y - 1 - x;
				collisionData[y * stageSize.x + x] = buffer[(stageSize.y - 1 - x) * stageSize.x + y];
			}
		}
	}
	if( input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_D))
	{
		rotateCount++;
		vector<int> buffer = collisionData;
		for( int y = 0, posY = stageSize.y - 1; y < stageSize.y; y++, posY--)
		{
			for( int x = 0, posX = stageSize.x - 1; x < stageSize.x; x++, posX--)
			{
				collisionData[y * stageSize.x + x] = buffer[(stageSize.y - 1 - posX) * stageSize.x + posY];
			}
		}
	}
	
	int rotValue = 90 * rotateCount - stageAngle;
	
	if( rotValue > 0)
	{
		angle = 1;
		stageAngle += 1;
	}
	else if( rotValue < 0)
	{
		angle = -1;
		stageAngle -= 1;
	}

	const float sin_f = sinf( angle.getRadian());
	const float cos_f = cosf( angle.getRadian());

	for( int y = 0; y < stageSize.y; y++)
	{
		for( int x = 0; x < stageSize.x; x++)
		{
			const int arrayNumber = y * stageSize.x + x;
			const float posX = chipPosition[arrayNumber].x;
			const float posY = chipPosition[arrayNumber].y;
			const float cx = screenSize.x / 2;
			const float cy = screenSize.y / 2;

			chipPosition[arrayNumber].x = (posX - cx) * cos_f - (posY - cy) * sin_f + cx;
			chipPosition[arrayNumber].y = (posX - cx) * sin_f + (posY - cy) * cos_f + cy;
		}
	}

	chip -> setRotation( -DEGREE_TO_RADIAN( stageAngle));
}

void Stage::draw(void)
{
	for ( int i = 0; i < chipCount; i++)
	{
		const int chipNumber = stageData[chipCount - i - 1];
		if( chipNumber < 0) { continue; }

		chip -> setPosition( chipPosition[i]);
		chip -> draw( chipNumber);
	}
}

int Stage::getRotateDegree( void)
{
	return stageAngle;
}

float Stage::getRotateRadian( void)
{
	return DEGREE_TO_RADIAN( stageAngle);
}

int Stage::getChipNumbr( int x, int y)
{
	const int firstPosX = (screenSize.x / 2) - ( (stageSize.x / 2) * chipSize.x);
	const int firstPosY = (screenSize.y / 2) + ( (stageSize.y / 2) * chipSize.y);

	if( x < firstPosX || y > firstPosY || x  > firstPosX + chipSize.x * stageSize.x || y < firstPosY - chipSize.y * stageSize.y)
	{
		assert( !"Stage Array Out Access");
		return -1;
	}

	int countX = (x - firstPosX) / chipSize.x;
	int countY = (firstPosY - y) / chipSize.y;

	return collisionData[countY * stageSize.x + countX];
}
