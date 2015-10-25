
#include <cassert>
#include "../Game/ResourceManager.h"
#include "../Game/StageConfig.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "Edit.h"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();
static StageConfig* stageConfig = StageConfig::getInstance();

Edit::Edit() : chipTable(nullptr)
{
	
	chip = instance -> getSprites("mapchip");
	chipSize = chip -> getTextureSizeX();

	edit_bgm = LibSound::create("bgm/edit.wav");

	material_logo = CatGameLib::LibSprite::create( "logo/material.png");

	grid_size[0] = CatGameLib::LibSprite::create( "background/grid14.png");
	grid_size[1] = CatGameLib::LibSprite::create( "background/grid16.png");
	grid_size[2] = CatGameLib::LibSprite::create( "background/grid18.png");

	chipTable = CatGameLib::LibSprite::create( "background/chipTable.png");
}

Edit::~Edit()
{
}

void Edit::init(void)
{
	input = LibInput::getInstance();

	edit_bgm -> setVolume(0.0f);
	edit_bgm -> setLoop(true);


	instance -> getSprites("books") -> setPosition(sWHeaf + 200, sHHeaf);

	stageConfig -> setSizeNumber(stageConfig -> getSizeNumber());
	stageConfig -> setBgNumber(stageConfig -> getBgNumber());
	stageConfig -> setMusicNumber(stageConfig -> getMusicNumber());

	for(int i = 0; i <= 2; i++)
	{
		grid_size[i] -> setPosition(sWHeaf - 170, sHHeaf);
		grid_size[i] -> setScale(1.0f);
		grid_size[i] -> setAlpha(0.0f);
	}

	for( int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back( instance -> getSprite( bgName.c_str()));
		bgTextures[i - 1] -> setPosition(sWHeaf - 170, sHHeaf);
		bgTextures[i - 1] -> setScale(0.7f);
		bgTextures[i - 1] -> setAlpha(0.0f);
	}

	instance -> getSprite("back") -> setPosition(sWHeaf + 450, sHHeaf - 300);
	instance -> getSprite("back") -> setScale( 0.8f);
	instance -> getSprite("back") -> setAlpha(0.0f);

	material_logo -> setPosition(sWHeaf +450, sHHeaf + 300);
	material_logo -> setScale(1.5f);
	material_logo -> setAlpha(0.0f);

	chipTable -> setPosition(sWHeaf + 450, sHHeaf + 50);
	chipTable -> setScale( 1.0f);
	chipTable -> setAlpha(0.0f);

	chip -> setPosition(sWHeaf +450, sHHeaf + 300);
	chip -> setScale( 1.0f);
	chip -> setAlpha(0.0f);

	Volume = 0;
	volumeFlag = 0;
	anime_number = BOOK_ANM_MIN;
}

void Edit::update(void)
{
	if(edit_bgm -> getState() != LibSound::Play)
	{
		edit_bgm -> play();
	}

	if(volumeFlag == 1)
	{
		Volume -= 0.02f;
		edit_bgm -> setVolume(Volume);
	}
	else if(Volume <= 1.0 && volumeFlag == 0)
	{
		Volume += 0.01f;
		edit_bgm -> setVolume(Volume);
	}

	
	pictFade();
	editDraw();

	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}

}

void Edit::pictFade(void)
{
	if(grid_size[stageConfig -> getSizeNumber()] -> getAlpha() < 255)
	{
		grid_size[stageConfig -> getSizeNumber()] -> setAlpha(grid_size[stageConfig -> getSizeNumber()] -> getAlpha() + 5);
	}

	if(bgTextures[stageConfig -> getBgNumber()] -> getAlpha() < 255)
	{
		bgTextures[stageConfig -> getBgNumber()] -> setAlpha(bgTextures[stageConfig -> getBgNumber()] -> getAlpha() + 5);
	}

	if(instance -> getSprite("back") -> getAlpha() < 255)
	{
		instance -> getSprite("back") -> setAlpha(instance -> getSprite("back") -> getAlpha() + 5);
	}

	if(material_logo -> getAlpha() < 255)
	{
		material_logo -> setAlpha(material_logo -> getAlpha() + 5);
	}

	if(chipTable -> getAlpha() < 255)
	{
		chipTable -> setAlpha(chipTable -> getAlpha() + 5);
	}

	if(chip -> getAlpha() < 255)
	{
		chip -> setAlpha( chip -> getAlpha() + 5);
	}
}

void Edit::editDraw(void)
{
	instance -> getSprite("floar") -> draw();
	instance -> getSprites("books") -> draw(anime_number);
	bgTextures[stageConfig -> getBgNumber()] -> draw();
	grid_size[stageConfig -> getSizeNumber()] -> draw();
	instance -> getSprite("back") -> draw();
	material_logo -> draw();
	chipTable -> draw();
	/*for(int i = 1; i <= 36; i++)
	{
		chip -> draw(i);
	}*/
}