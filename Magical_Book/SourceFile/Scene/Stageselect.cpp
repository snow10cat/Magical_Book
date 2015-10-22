
#include "../Game/SpriteManager.h"
#include "CatGameLib.h"
#include "Stageselect.h"


using namespace CatGameLib;
using namespace MagicalBook;

static SpriteManager* instance = SpriteManager::getInstance();

Stageselect::Stageselect() : frame(nullptr),
							 make(nullptr)
{
	frame = LibSprite::create("background/frame.png");
	make = LibSprite::create("logo/make.png");
}


Stageselect::~Stageselect()
{
}


void Stageselect::init(void)
{
	input = LibInput::getInstance();

	instance -> getSprites("books") -> setPosition(sWHeaf + 300, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);

	instance -> getSprite("game_bg1") -> setPosition(sWHeaf - 210, sHHeaf + 160);
	instance -> getSprite("game_bg1") -> setScale(0.35f);

	instance -> getSprite("game_bg2") -> setPosition(sWHeaf + 90, sHHeaf + 160);
	instance -> getSprite("game_bg2") -> setScale(0.3f);

	instance -> getSprite("game_bg3") -> setPosition(sWHeaf - 210, sHHeaf - 140);
	instance -> getSprite("game_bg3") -> setScale(0.3f);

	instance -> getSprite("game_bg4") -> setPosition(sWHeaf + 90, sHHeaf - 140);
	instance -> getSprite("game_bg4") -> setScale(0.3f);

	frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
	frame -> setScale(0.35f);

	make -> setPosition(sWHeaf + 500, sHHeaf + 200);
	make -> setScale(0.8f);

	counter = 0;
	flag = 0;
	anime_number = 0;
	size = 1;
	select_work = ModeSelect;
}



void Stageselect::update(void)
{
	instance -> getSprite("floar") -> draw();
	instance -> getSprites("books") -> draw(0);
	instance -> getSprite("game_bg1") -> draw();
	instance -> getSprite("game_bg2") -> draw();
	instance -> getSprite("game_bg3") -> draw();
	instance -> getSprite("game_bg4") -> draw();


	switch(select_work)
	{
	case ModeSelect:
		break;

	case Animation:
		break;

	case GameMode:
		break;

	case EditMode:
		break;

	case Fadeout:
		break;

	case Next:
		break;
	}


	frame -> draw();
	make -> draw();

	if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Left))
	{
		counter--;
	}
	if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
	{
		counter++;
	}
	if (input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Up) || input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Down))
	{
		counter += 2;
	}

	if (counter % 4 == 0)
	{
		flag = 0;
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
		}
	}
	else if (counter % 4 == 1)
	{
		flag = 1;
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
		}
	}
	else if (counter % 4 == 2)
	{
		flag = 2;
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
		}
	}
	else if (counter % 4 == 3)
	{
		flag = 3;
		if (input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Z))
		{
			counter = 0;
		}
	}
/*
	if(flag == 0)
	{
		instance -> getSprite("game_bg1") -> setScale(0.35f);
		instance -> getSprite("game_bg2") -> setScale(0.3f);
		instance -> getSprite("game_bg3") -> setScale(0.3f);
		instance -> getSprite("game_bg4") -> setScale(0.3f);
		frame -> setPosition(sWHeaf - 210, sHHeaf + 160);
	}
	else if(flag == 1)
	{
		instance -> getSprite("game_bg2") -> setScale(0.35f);
		instance -> getSprite("game_bg1") -> setScale(0.3f);
		instance -> getSprite("game_bg3") -> setScale(0.3f);
		instance -> getSprite("game_bg4") -> setScale(0.3f);
		frame -> setPosition(sWHeaf + 90, sHHeaf + 160);
	}
	else if(flag == 2)
	{
		instance -> getSprite("game_bg3") -> setScale(0.35f);
		instance -> getSprite("game_bg1") -> setScale(0.3f);
		instance -> getSprite("game_bg2") -> setScale(0.3f);
		instance -> getSprite("game_bg4") -> setScale(0.3f);
		frame -> setPosition(sWHeaf - 210, sHHeaf - 140);
	}
	else if(flag == 3)
	{
		instance -> getSprite("game_bg4") -> setScale(0.35f);
		instance -> getSprite("game_bg1") -> setScale(0.3f);
		instance -> getSprite("game_bg2") -> setScale(0.3f);
		instance -> getSprite("game_bg3") -> setScale(0.3f);
		frame -> setPosition(sWHeaf + 90, sHHeaf - 140);
	}
	*/
}