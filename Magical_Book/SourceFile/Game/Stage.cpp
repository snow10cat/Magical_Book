
#include "CatGameLib.h"
#include "FileManager.h"
#include "ResourceManager.h"
#include "Stage.h"

// #include <algorithm>

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

static int bgAlpha = 0;

Stage::Stage() : chipCount(0),
				 stageAngle(0),
				 rotateCount(0)
{
	screenSize = LibMain::getInstance() -> getScreenSize();
	floor = ResourceManager::getInstance() -> getSprite("floar");
	floor -> setPosition(screenSize.x * 0.5f, screenSize.y * 0.5f);
	chip = ResourceManager::getInstance() -> getSprites("mapchip");
	chipSize = chip -> getTextureSizeX();


	StageFile* file = FileManager::getInstance() -> loadFile(FileManager::getInstance() -> getFileName(0));

	stageData = file -> getStageData();
	collisionData = stageData;
	stageSize.x = file -> getStageSize().x;
	stageSize.y = file -> getStageSize().y;

	bgNumber = file -> getBGNumber();
	musicNumber = file -> getMusicNumber();

	delete file;
	file = nullptr;

	drawStartingPos.x = (screenSize.x / 2) - ((stageSize.x / 2) * chipSize.x) + chipSize.x * chip -> getAnchorPointX();
	drawStartingPos.y = (screenSize.y / 2) - ((stageSize.y / 2) * chipSize.y) + chipSize.y * chip -> getAnchorPointY();

	chipCount = stageSize.x * stageSize.y;

	chipPosition.resize(chipCount);

	for(int y = 0; y < stageSize.y; y++)
	{
		for(int x = 0, posX = stageSize.x - 1; x < stageSize.x; x++, posX--)
		{
			const int arrayNumber = y * stageSize.x + x;
			chipPosition[arrayNumber].x = drawStartingPos.x + posX * chipSize.x;
			chipPosition[arrayNumber].y = drawStartingPos.y + y * chipSize.y;
		}
	}

	books = ResourceManager::getInstance() -> getSprites("books");
	switch(bgNumber)
	{
	case ResourceManager::BgName::BG_Castle:
		bg = ResourceManager::getInstance() -> getSprite("game_bg1");
		break;

	case ResourceManager::BgName::BG_Table:
		bg = ResourceManager::getInstance() -> getSprite("game_bg2");
		break;

	case ResourceManager::BgName::BG_Gate:
		bg = ResourceManager::getInstance() -> getSprite("game_bg3");
		break;

	case ResourceManager::BgName::BG_Window:
		bg = ResourceManager::getInstance() -> getSprite("game_bg4");
		break;

	case ResourceManager::BgName::BG_Throne:
		bg = ResourceManager::getInstance() -> getSprite("game_bg5");
		break;
	}

	books -> setPosition(screenSize.x * 0.5f, screenSize.y * 0.5f);
	books -> setScale(1.6f);
	books -> setAnchorPointX(0.3f);

	bg -> setPosition(screenSize.x * 0.5f, screenSize.y * 0.5f);
	bgAlpha = bg -> getAlpha();
	bg -> setAlpha(255.0f);

	switch((int)stageSize.x)
	{
	case StageSize::Small:
		bg -> setScale(0.6f);
		break;

	case StageSize::Medium:
		bg -> setScale(0.7f);
		break;

	case StageSize::Large:
		bg -> setScale(0.8f);
		break;
	}

	switch(musicNumber)
	{
	case ResourceManager::BgmNum::BGM_1:
		bgm = ResourceManager::getInstance() -> getSound("bgm1");
		break;
	case ResourceManager::BgmNum::BGM_2:
		bgm = ResourceManager::getInstance() -> getSound("bgm2");
		break;
	case ResourceManager::BgmNum::BGM_3:
		bgm = ResourceManager::getInstance() -> getSound("bgm3");
		break;
	}
	bgm -> setLoop(true);
	bgm -> play();

}

Stage::~Stage()
{
	bg -> setAlpha(bgAlpha);
	books -> setAnchorPointX(0.5f);
}

void Stage::update(void)
{
	LibCircle angle = 0;
	LibInput* input = LibInput::getInstance();

	int rotValue = 90 * rotateCount - stageAngle;
	
	if(rotValue > 0)
	{
		angle = 1;
		stageAngle += 1;
	}
	else if(rotValue < 0)
	{
		angle = -1;
		stageAngle -= 1;
	}
	else
	{
		if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_F))
		{
			rotateCount--;
			vector<unsigned char> buffer = collisionData;
			for(int y = 0; y < stageSize.y; y++)
			{
				for(int x = 0; x < stageSize.x; x++)
				{
					collisionData[y * stageSize.x + x] = buffer[(stageSize.y - 1 - x) * stageSize.x + y];
				}
			}
		}
		if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_D))
		{
			rotateCount++;
			vector<unsigned char> buffer = collisionData;
			for(int y = 0, posY = stageSize.y - 1; y < stageSize.y; y++, posY--)
			{
				for(int x = 0, posX = stageSize.x - 1; x < stageSize.x; x++, posX--)
				{
					collisionData[y * stageSize.x + x] = buffer[(stageSize.y - 1 - posX) * stageSize.x + posY];
				}
			}
		}
	}

	const float sin_f = sinf(angle.getRadian());
	const float cos_f = cosf(angle.getRadian());

	for(int y = 0; y < stageSize.y; y++)
	{
		for(int x = 0; x < stageSize.x; x++)
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

	bg -> setRotation(-stageAngle);
	books -> setRotation(-stageAngle);
	chip -> setRotation(-stageAngle);
}

void Stage::draw(void)
{
	floor -> draw();
	books -> draw(0);
	bg -> draw();

	for (int i = 0; i < chipCount; i++)
	{
		const int chipNumber = stageData[chipCount - i - 1];
		if(chipNumber < 0) { continue; }

		chip -> setPosition(chipPosition[i]);
		chip -> draw(chipNumber);
	}
}

int Stage::getRotateCount(void)
{
	return rotateCount;
}

int Stage::getRotateDegree(void)
{
	return stageAngle;
}

float Stage::getRotateRadian(void)
{
	return DEGREE_TO_RADIAN(stageAngle);
}

int Stage::getChipNumber(int x, int y)
{
	const int firstPosX = (screenSize.x / 2) - ((stageSize.x / 2) * chipSize.x);
	const int firstPosY = (screenSize.y / 2) + ((stageSize.y / 2) * chipSize.y);

	if(x < firstPosX || y > firstPosY || x  > firstPosX + chipSize.x * stageSize.x || y < firstPosY - chipSize.y * stageSize.y)
	{
		assert(!"Stage Array Out Access");
		return -1;
	}

	int countX = (x - firstPosX) / chipSize.x;
	int countY = (firstPosY - y) / chipSize.y;

	return collisionData[countY * stageSize.x + countX];
}

LibVector2 Stage::getChipPosition(int x, int y)
{
	const int firstPosX = (screenSize.x / 2) - ((stageSize.x / 2) * chipSize.x);
	const int firstPosY = (screenSize.y / 2) + ((stageSize.y / 2) * chipSize.y);

	if(x < firstPosX || y > firstPosY || x  > firstPosX + chipSize.x * stageSize.x || y < firstPosY - chipSize.y * stageSize.y)
	{
		assert(!"Stage Array Out Access");
		return -1;
	}

	int countX = (x - firstPosX) / chipSize.x;
	int countY = (firstPosY - y) / chipSize.y;

	LibVector2 pos(firstPosX - chipSize.x * countX, firstPosY - chipSize.y * countY);

	return pos;
}
