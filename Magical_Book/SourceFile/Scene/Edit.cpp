//TODO コメントの追加、ソースの整理 

#include <cassert>
#include "../Game/ResourceManager.h"
#include "../Game/StageConfig.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "../Game/FileManager.h"
#include "Edit.h"

#define COUNTER 25

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

static StageConfig* stageConfig = StageConfig::getInstance();


Edit::Edit() : editBgm(nullptr),
			   materialLogo(nullptr),
			   chipTable(nullptr),
			   save(nullptr),
			   redo(nullptr),
			   undo(nullptr),
			   pointer(nullptr)
{

	editBgm = LibSound::create("bgm/edit.wav");

	materialLogo = CatGameLib::LibSprite::create("logo/material.png");

	gridSize[Grid::S] = CatGameLib::LibSprite::create("background/grid14.png");
	gridSize[Grid::M] = CatGameLib::LibSprite::create("background/grid16.png");
	gridSize[Grid::L] = CatGameLib::LibSprite::create("background/grid18.png");

	chipTable = CatGameLib::LibSprite::create("background/chipTable.png");
	
	//素材
	materials[MaterialNum::Chip] = LibSprites::create("mapchip/mapchip.png", 34, 34);
	materials[MaterialNum::Player] = LibSprites::create("player/player.png", 34, 68);
	materials[MaterialNum::Enemy] = LibSprites::create("enemy/crayon_red.png", 34, 68);
	materials[MaterialNum::Door] = LibSprites::create("gimmick/door_up.png", 42, 68);
	materials[MaterialNum::Gimmick] = LibSprites::create("gimmick/gimmick_up.png", 34, 68);

	save = CatGameLib::LibSprite::create("logo/save.png");

	pointer = CatGameLib::LibSprite::create("logo/pointer.png");
}

Edit::~Edit()
{
}

void Edit::init(void)
{
	input = LibInput::getInstance();

	books = ResourceManager::getInstance() -> getSprites("books");

	back = ResourceManager::getInstance() -> getSprite("back");


	volume = 0;
	volumeFlag = true;

	//音声
	editBgm -> setVolume(0.0f);
	editBgm -> setLoop(true);


	books -> setPosition(sWHeaf + 200, sHHeaf);

	stageConfig -> setSizeNumber(stageConfig -> getSizeNumber());
	stageConfig -> setBgNumber(stageConfig -> getBgNumber());
	stageConfig -> setMusicNumber(stageConfig -> getMusicNumber());

	gridSize[stageConfig -> getSizeNumber()] -> setPosition(sWHeaf - 170, sHHeaf);
	gridSize[stageConfig -> getSizeNumber()] -> setScale(1.0f);
	gridSize[stageConfig -> getSizeNumber()] -> setAlpha(0.0f);

	for(int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back(ResourceManager::getInstance() -> getSprite(bgName.c_str()));
		bgTextures[i - 1] -> setPosition(sWHeaf - 170, sHHeaf);
		bgTextures[i - 1] -> setScale(0.7f);
		bgTextures[i - 1] -> setAlpha(0.0f);
	}

	//素材
	materials[MaterialNum::Chip] -> setPosition(sWHeaf + 350, sHHeaf + 200);
	materials[MaterialNum::Player] -> setPosition(sWHeaf + 350, sHHeaf + 68);
	materials[MaterialNum::Enemy] -> setPosition(sWHeaf + 400, sHHeaf + 68);
	materials[MaterialNum::Door] -> setPosition(sWHeaf + 450, sHHeaf + 68);
	materials[MaterialNum::Gimmick] -> setPosition(sWHeaf + 500, sHHeaf + 68);

	for(int i = 0; i < MaterialNum::MaterialCount; i++)
	{
		materials[i] -> setScale(1.0f);
		materials[i] -> setAlpha(0.0f);
	}

	materialLogo -> setPosition(sWHeaf +450, sHHeaf + 300);
	materialLogo -> setScale(1.5f);
	materialLogo -> setAlpha(0.0f);

	chipTable -> setPosition(sWHeaf + 450, sHHeaf);
	chipTable -> setScale(1.0f);
	chipTable -> setAlpha(0.0f);

	pointer -> setPosition(sWHeaf + 350+17, sHHeaf + 200-17);
	pointer -> setScale(1.0f);
	pointer -> setAlpha(0.0f);

	save -> setPosition(sWHeaf + 550, sHHeaf - 200);
	save -> setScale(0.7f);
	save -> setAlpha(0.0f);

	back -> setPosition(sWHeaf + 450, sHHeaf - 300);
	back -> setScale(0.8f);
	back -> setAlpha(0.0f);

	screenSize = LibMain::getInstance() -> getScreenSize();
	
	if(stageConfig -> getSizeNumber() == 0)
	{
		stageSize = Small;
	}
	else if(stageConfig -> getSizeNumber() == 1)
	{
		stageSize = Medium;
	}
	else if(stageConfig -> getSizeNumber() == 2)
	{
		stageSize = Large;
	}

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

	counter = 0;

	chipNum = 1;
	chipState = 0;
	chipDirection = 0;
	chipCounter = 0;
	chipHave = 0;

	materialRow = 1;
	materialCol = 1;

	materialSetRow = 1;
	materialSetCol = 1;

	anime_number = BOOK_ANM_MIN;

	edit_work = Fadein;
	edit_set_work = MaterialSelect;
}

void Edit::update(void)
{
	playSound();
	
	editDraw();

	materialDraw();


	switch (edit_work)
	{
	case Fadein:
		pictFade();
		break;
	case EditSet:
		edit();
		break;
	case BackAnimation:
	//	backAnimation();
		break;
	case Animation:
	//	animation();
		break;
	case Next:
	//	next();
		break;

	default:
		assert(!"不正な状態");
		break;
	}
	
	//あとで消す
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}

}


/**
 *	@brief 音声再生
 *
 *	@author	Tatsuya Maeda
 */
void Edit::playSound(void)
{
	if (editBgm -> getState() != LibSound::Play)
	{
		editBgm -> play();
	}

	if (volumeFlag == false)
	{
		volume -= BGM_FADE;
		editBgm -> setVolume(volume);
	}
	else if(volume <= MAX_VOLUME && volumeFlag == true)
	{
		volume += BGM_FADE;
		editBgm -> setVolume(volume);
	}
}


//フェードイン
void Edit::pictFade(void)
{
	if(gridSize[stageConfig -> getSizeNumber()] -> getAlpha() < 255)
	{
		gridSize[stageConfig -> getSizeNumber()] -> setAlpha(gridSize[stageConfig -> getSizeNumber()] -> getAlpha() + 5);
	}

	if(bgTextures[stageConfig -> getBgNumber()] -> getAlpha() < 255)
	{
		bgTextures[stageConfig -> getBgNumber()] -> setAlpha(bgTextures[stageConfig -> getBgNumber()] -> getAlpha() + 5);
	}

	if(materialLogo -> getAlpha() < 255)
	{
		materialLogo -> setAlpha(materialLogo -> getAlpha() + 5);
	}

	if(chipTable -> getAlpha() < 255)
	{
		chipTable -> setAlpha(chipTable -> getAlpha() + 5);
	}

	if(pointer -> getAlpha() < 255)
	{
		pointer -> setAlpha(pointer -> getAlpha() + 5);
	}
	
	//素材
	for(int i = 0; i < MaterialNum::MaterialCount; i++)
	{
		if (materials[i] -> getAlpha() < 255)
		{
			materials[i] -> setAlpha(materials[i] -> getAlpha() + FADE);
		}
		else
		{
			materials[i] -> setAlpha(255);
		}
	}

	if(save -> getAlpha() < 255)
	{
		save -> setAlpha(save -> getAlpha() + 5);
	}

	if(back -> getAlpha() < 255)
	{
		back -> setAlpha(back -> getAlpha() + 5);
	}
	else
	{
		edit_work = EditSet;
	}

}


void Edit::edit(void)
{
	switch (edit_set_work)
	{
	case MaterialSelect:
		materialSelect();
		break;
	case MaterialSet:
		materialSet();
		break;
	default:
		assert(!"不正な状態");
		break;
	}
}


//素材選択
void Edit::materialSelect(void)
{
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
		materialSetRow = stageSize.x / 2;
		materialSetCol = stageSize.y / 2;

		if(materialRow == 1)
		{
			chipHave = 1;
			if(materialCol == 1)
			{
				chipNum = 1;
			}
			else if(materialCol == 2)
			{
				chipNum = 5;
			}
			else if(materialCol == 3)
			{
				chipNum = 9;
			}
			else if(materialCol == 4)
			{
				chipNum = 13;
			}
			else if(materialCol == 5)
			{
				chipNum = 17;
			}
		}
		else if(materialRow == 2)
		{
			chipHave = 1;
			if(materialCol == 1)
			{
				chipNum = 21;
			}
			else if(materialCol == 2)
			{
				chipNum = 25;
			}
			else if(materialCol == 3)
			{
				chipNum = 29;
			}
			else if(materialCol == 4)
			{
				chipNum = 33;
			}
		}
		else if(materialRow == 3)
		{
			chipState = materialCol;
			chipHave = 2;
		}
		edit_set_work = MaterialSet;
	}

	if(materialRow == 1 && materialCol == 5)
	{
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
		{
			materialRow--;
			materialCol--;
		}
	}
	else
	{
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
		{
			materialRow--;
		}
		if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Up))
		{
			counter++;
			if(counter >= COUNTER && counter % 5 == 1)
			{
				materialRow--;
			}
		}
		else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Up))
		{
			counter = 0;
		}
	}
	if(materialRow == 1 && materialCol == 5)
	{
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			materialRow++;
			materialCol--;
		}
	}
	else
	{
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
		{
			materialRow++;
		}

		if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter++;
			if(counter >= COUNTER && counter % 5 == 1)
			{
				materialRow++;
			}
		}
		else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Down))
		{
			counter = 0;
		}
	}
	
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		if(materialRow % 4 != 0)
		{
			materialCol--;
		}
	}
	if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Left))
	{
		counter++;
		if(counter >= COUNTER && counter % 5 == 1)
		{
			materialCol--;
		}
	}
	else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Left))
	{
		counter = 0;
	}
	
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		if(materialRow % 4 != 0)
		{
			materialCol++;
		}
	}
	if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Right))
	{
		counter++;
		if(counter >= COUNTER && counter % 5 == 1)
		{
			materialCol++;
		}
	}
	else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Right))
	{
		counter = 0;
	}
	

	materialRow = LibBasicFunc::wrap(materialRow, 0, 4);
	if(materialRow == 1)
	{
		materialCol = LibBasicFunc::wrap(materialCol, 0, 6);
	}
	else
	{
		materialCol = LibBasicFunc::wrap(materialCol, 0, 5);
	}

	if(materialRow % 4 == 0)
	{
		pointer -> setPosition(sWHeaf + 450, sHHeaf - 310);
		back -> setScale(1.0f);
	}
	else if(materialRow % 4 == 3)
	{
		pointer -> setPositionY(sHHeaf + 200-17 - (materialRow - 1 + 1) * 50);
		back -> setScale(0.8f);
	}
	else
	{
		pointer -> setPositionY(sHHeaf + 200-17 - (materialRow - 1) * 60);
		back -> setScale(0.8f);
	}

	if(materialRow == 1)
	{
		if(materialCol % 6 == 0)
		{
			materialSetRow = 1;
			edit_set_work = MaterialSet;
		}
		else
		{
			pointer -> setPositionX(sWHeaf + 350+17 + (materialCol - 1) * 50);
		}
	}
	else
	{
		if(materialRow % 4 != 0)
		{
			if(materialCol % 5 == 0)
			{
				materialSetRow = 1;
				edit_set_work = MaterialSet;
			}
			else
			{
				pointer -> setPositionX(sWHeaf + 350+17 + (materialCol - 1) * 50);
			}
		}
	}

	if(chipHave == 0)
	{
		if(materialCol == 4 || materialCol == 5)
		{
			materialSetCol = 1;
		}
		else if(materialCol == 1)
		{
			materialSetCol = stageSize.x;
		}
	}
	else if(chipHave == 1)
	{
//		chip -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+17);
	}
	else if(chipHave == 2)
	{
		/*if(materialCol == 1)
		{
			player -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+34);
		}
		else if(materialCol == 2)
		{
			enemy -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+34);
		}
		else if(materialCol == 3)
		{
			door -> setPosition(pointer -> getPositionX()-21, pointer -> getPositionY()+34);
		}
		else if(materialCol == 4)
		{
			gimmick -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+34);
		}*/
	}
}


//素材配置
void Edit::materialSet(void)
{
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
	{
//		chip -> setPosition(chip -> getPosition());
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Up))
	{
		materialSetRow--;
	}
	if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Up))
	{
		counter++;
		if(counter >= COUNTER && counter % 5 == 1)
		{
			materialSetRow--;
		}
	}
	else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Up))
	{
		counter = 0;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		materialSetRow++;
	}
	if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Down))
	{
		counter++;
		if(counter >= COUNTER && counter % 5 == 1)
		{
			materialSetRow++;
		}
	}
	else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Down))
	{
		counter = 0;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
	{
		materialSetCol--;
	}
	if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Left))
	{
		counter++;
		if(counter >= COUNTER && counter % 5 == 1)
		{
			materialSetCol--;
		}
	}
	else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Left))
	{
		counter = 0;
	}

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		materialSetCol++;
	}
	if (input -> getKeyboardState(LibInput::KeyBoardNumber::Key_Right))
	{
		counter++;
		if(counter >= COUNTER && counter % 5 == 1)
		{
			materialSetCol++;
		}
	}
	else if (input -> getKeyboardUpState(LibInput::KeyBoardNumber::Key_Right))
	{
		counter = 0;
	}
	
	chipDirection = LibBasicFunc::wrap(chipDirection, 0, 4);

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_D))
	{
		chipDirection--;

		if(chipDirection != -1)
		{
			chipNum -= 1;
		}
		else
		{
			chipNum += 3;
		}
	}
	else if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_F))
	{
		chipDirection++;

		if(chipDirection != 4)
		{
			chipNum += 1;
		}
		else
		{
			chipNum -= 3;
		}
	}

	if(chipHave == 1)
	{
//		chip -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+17);
	}
	else if(chipHave == 2)
	{
		/*if(chipState == 1)
		{
			player -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+34);
		}
		else if(chipState == 2)
		{
			enemy -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+34);
		}
		else if(chipState == 3)
		{
			door -> setPosition(pointer -> getPositionX()-18, pointer -> getPositionY()+34);
		}
		else if(chipState == 4)
		{
			gimmick -> setPosition(pointer -> getPositionX()-17, pointer -> getPositionY()+34);
		}*/
	}

	if(stageConfig -> getSizeNumber() == 0)
	{
		materialSetRow = CatGameLib::LibBasicFunc::wrap(materialSetRow, 0, 14);
		materialSetCol = CatGameLib::LibBasicFunc::wrap(materialSetCol, 0, 15);
	}
	else if(stageConfig -> getSizeNumber() == 1)
	{
		materialSetRow = CatGameLib::LibBasicFunc::wrap(materialSetRow, 0, 16);
		materialSetCol = CatGameLib::LibBasicFunc::wrap(materialSetCol, 0, 17);
	}
	else if(stageConfig -> getSizeNumber() == 2)
	{
		materialSetRow = CatGameLib::LibBasicFunc::wrap(materialSetRow, 0, 18);
		materialSetCol = CatGameLib::LibBasicFunc::wrap(materialSetCol, 0, 19);
	}

	if(stageConfig -> getSizeNumber() == 0)
	{
		if(materialSetRow % 14 == 0)
		{
			pointer -> setPositionY(sHHeaf + 35 * (materialSetRow - stageSize.y / 2));
		}
		else
		{
			pointer -> setPositionY(sHHeaf - 35 * (materialSetRow - stageSize.y / 2));
		}
		
		if(materialSetCol % 15 == 0)
		{
			materialRow = 1;
			chipHave = 0;
			chipDirection = 0;
			edit_set_work = MaterialSelect;
		}
		else
		{
			pointer -> setPositionX(sWHeaf - 170 + 35 * (materialSetCol - stageSize.y / 2));
		}
	}
	else if(stageConfig -> getSizeNumber() == 1)
	{
		if(materialSetRow % 16 == 0)
		{
			pointer -> setPositionY(sHHeaf + 35 * (materialSetRow - stageSize.y / 2));
		}
		else
		{
			pointer -> setPositionY(sHHeaf - 35 * (materialSetRow - stageSize.y / 2));
		}

		if(materialSetCol % 17 == 0)
		{
			materialRow = 1;
			chipHave = 0;
			chipDirection = 0;
			edit_set_work = MaterialSelect;
		}
		else
		{
			pointer -> setPositionX(sWHeaf - 170 + 35 * (materialSetCol - stageSize.y / 2));
		}
	}
	else if(stageConfig -> getSizeNumber() == 2)
	{
		if(materialSetRow % 18 == 0)
		{
			pointer -> setPositionY(sHHeaf + 35 * (materialSetRow - stageSize.y / 2));
		}
		else
		{
			pointer -> setPositionY(sHHeaf - 35 * (materialSetRow - stageSize.y / 2));
		}

		if(materialSetCol % 19 == 0)
		{
			materialRow = 1;
			chipHave = 0;
			chipDirection = 0;
			edit_set_work = MaterialSelect;
		}
		else
		{
			pointer -> setPositionX(sWHeaf - 170 + 35 * (materialSetCol - stageSize.y / 2));
		}
	}

	if(materialSetCol == 1)
	{
		materialCol = 5;
	}
	else if(materialSetCol == stageSize.x)
	{
		materialCol = 1;
	}
}


void Edit::editDraw(void)
{
	ResourceManager::getInstance() -> getSprite("floor") -> draw();
	books -> draw(anime_number);
	bgTextures[stageConfig -> getBgNumber()] -> draw();
	gridSize[stageConfig -> getSizeNumber()] -> draw();

	if(chipHave == 1)
	{
//		chip -> draw(chipNum);
	}
	else if(chipHave == 2)
	{
		/*if(chipState == 1)
		{
			player -> draw(0);
		}
		else if(chipState == 2)
		{
			enemy -> draw(0);
		}
		else if(chipState == 3)
		{
			door -> draw(0);
		}
		else if(chipState == 4)
		{
			gimmick -> draw(0);
		}*/
	}

	materialLogo -> draw();
	chipTable -> draw();
	
	chipCounter = 0;

	save -> draw();

	back -> draw();

	pointer -> draw();
}


void Edit::materialDraw(void)
{
	for(int i = 1; i <= 36; i += 4)
	{
		chipCounter = CatGameLib::LibBasicFunc::wrap(chipCounter, 0, 5);

		if(i <= 5 * 4)
		{
			materials[MaterialNum::Chip] -> setPosition(sWHeaf + 350 + chipCounter * 50, sHHeaf + 200);
		}
		else if(i > 5 * 4 && i <= 36)
		{
			materials[MaterialNum::Chip] -> setPosition(sWHeaf + 350 + chipCounter * 50, sHHeaf + 140);
		}
		chipCounter++;
		
		materials[MaterialNum::Chip] -> draw(i);
	}

	for(int i = 1; i < MaterialNum::MaterialCount; i++)
	{
		materials[i] -> draw(0);
	}
}

/*
void Edit::editChipSetDraw(void)
{
	materialLogo -> draw();
	chipTable -> draw();

	for(int i = 1; i <= 36; i += 4)
	{
		chipCounter = CatGameLib::LibBasicFunc::wrap(chipCounter, 0, 5);

		if(i <= 5 * 4)
		{
			chip -> setPosition(sWHeaf + 350 + chipCounter * 50, sHHeaf + 200);
		}
		else if(i > 5 * 4 && i <= 36)
		{
			chip -> setPosition(sWHeaf + 350 + chipCounter * 50, sHHeaf + 140);
		}
		chipCounter++;
		
		chip -> draw(i);
	}
	chipCounter = 0;

	ResourceManager::getInstance() -> getSprites("player") -> draw(0);
	ResourceManager::getInstance() -> getSprites("enemy") -> draw(0);
	ResourceManager::getInstance() -> getSprites("door") -> draw(0);
	ResourceManager::getInstance() -> getSprites("gimmick") -> draw(0);
	
	back -> draw();
}*/