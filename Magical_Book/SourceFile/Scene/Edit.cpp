
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

	player = instance -> getSprites("player");
	enemy = instance -> getSprites("enemy");
	gimmick = instance -> getSprites("gimmick");
	door = instance -> getSprites("door");


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
	instance -> getSprite("back") -> setScale(0.8f);
	instance -> getSprite("back") -> setAlpha(0.0f);

	player -> setPosition(sWHeaf + 350, sHHeaf + 68);
	player -> setScale(1.0f);
	player -> setAlpha(0.0f);

	enemy -> setPosition(sWHeaf + 400, sHHeaf + 68);
	enemy -> setScale(1.0f);
	enemy -> setAlpha(0.0f);

	gimmick -> setPosition(sWHeaf + 450, sHHeaf + 68);
	gimmick -> setScale(1.0f);
	gimmick -> setAlpha(0.0f);

	door -> setPosition(sWHeaf + 500, sHHeaf + 68);
	door -> setScale(1.0f);
	door -> setAlpha(0.0f);

	material_logo -> setPosition(sWHeaf +450, sHHeaf + 300);
	material_logo -> setScale(1.5f);
	material_logo -> setAlpha(0.0f);

	chipTable -> setPosition(sWHeaf + 450, sHHeaf);
	chipTable -> setScale( 1.0f);
	chipTable -> setAlpha(0.0f);

	chip -> setPosition(sWHeaf + 350, sHHeaf + 220);
	chip -> setScale( 1.0f);
	chip -> setAlpha(0.0f);

	chipCounter = 0;

	Volume = 0;
	volumeFlag = 0;
	anime_number = BOOK_ANM_MIN;

	edit_work = Fadein;
}

void Edit::update(void)
{
	

	playSound();

	editDraw();

	switch (edit_work)
	{
	case Fadein:
		pictFade();
		break;
	case EditSelect:
		break;
	case Animation:
	//	animation();
		break;
	case Back:
	//	backAnimation();
		break;
	case Next:
	//	next();
		break;

	default:
		assert(!"•s³‚Èó‘Ô");
		break;
	}
	
	
	//‚ ‚Æ‚ÅÁ‚·
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_X))
	{
		LibSound::allStop();
		SceneManager::getInstance() -> createScene(SceneManager::SceneNumber::EditSelect);
	}

}


void Edit::playSound(void)
{
	if (edit_bgm->getState() != LibSound::Play)
	{
		edit_bgm->play();
	}

	if (volumeFlag == 1)
	{
		Volume -= 0.02f;
		edit_bgm->setVolume(Volume);
	}
	else if (Volume <= 1.0 && volumeFlag == 0)
	{
		Volume += 0.01f;
		edit_bgm->setVolume(Volume);
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

	if(player -> getAlpha() < 255)
	{
		player -> setAlpha(player -> getAlpha() + 5);
	}

	if(enemy -> getAlpha() < 255)
	{
		enemy -> setAlpha(enemy -> getAlpha() + 5);
	}

	if(gimmick -> getAlpha() < 255)
	{
		gimmick -> setAlpha(gimmick -> getAlpha() + 5);
	}

	if(door -> getAlpha() < 255)
	{
		door -> setAlpha(door -> getAlpha() + 5);
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

	chipCounter = 0;

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
	instance -> getSprites("player") -> draw(0);
	instance -> getSprites("enemy") -> draw(0);
	instance -> getSprites("gimmick") -> draw(0);
	instance -> getSprites("door") -> draw(0);
}