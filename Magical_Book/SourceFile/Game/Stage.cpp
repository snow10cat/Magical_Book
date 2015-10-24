
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

Stage::Stage() : stageSize( 0),
				 rotateCount( 0),
				 stageAngle( 0)
{
	chip = ResourceManager::getInstance() -> getSprites( "mapchip");
	screenSize = LibMain::getInstance() -> getScreenSize();
	chipSize = chip -> getTextureSizeX();

	collisionData = stageData;

	/*
		ここでステージデータ読み込み
	*/

	stageWidth = 16;
	stageHeight = 16;

	const int firstPosX = (screenSize.x / 2) - ( (stageWidth / 2) * chipSize.x) + chipSize.x * chip -> getAnchorPointX();
	const int firstPosY = (screenSize.y / 2) - ( (stageHeight / 2) * chipSize.y) + chipSize.y * chip -> getAnchorPointY();

	stageSize = stageWidth * stageHeight;

	chipPosition.resize( stageSize);

	for( int y = 0; y < stageHeight; y++)
	{
		for( int x = 0, posX = stageWidth - 1; x < stageWidth; x++, posX--)
		{
			const int arrayNumber = y * stageWidth + x;
			chipPosition[arrayNumber].x = firstPosX + posX * chipSize.x;
			chipPosition[arrayNumber].y = firstPosY + y * chipSize.y;
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

		for( int i = 0; i < collisionData.size(); i++)
		{

		}

		rotate( collisionData.rbegin(), collisionData.rbegin() + 1, collisionData.rend());
	}
	if( input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_D))
	{
		rotateCount++;
		rotate( collisionData.begin(), collisionData.begin() + 1, collisionData.end());
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

	for( int y = 0; y < stageHeight; y++)
	{
		for( int x = 0; x < stageWidth; x++)
		{
			const int arrayNumber = y * stageWidth + x;
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
	for ( int i = 0; i < stageSize; i++)
	{
		const int chipNumber = stageData[stageSize - i - 1];
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
	const int firstPosX = (screenSize.x / 2) - ( (stageWidth / 2) * chipSize.x);
	const int firstPosY = (screenSize.y / 2) + ( (stageHeight / 2) * chipSize.y);

	if( x < firstPosX || y > firstPosY || x  > firstPosX + chipSize.x * stageWidth || y < firstPosY - chipSize.y * stageHeight)
	{
		assert( !"Stage Array Out Access");
		return -1;
	}

	int countX = (x - firstPosX) / chipSize.x;
	int countY = (firstPosY - y) / chipSize.y;

	return collisionData[countY * stageWidth + countX];
}