
#include "Player.h"

#define GRAVITY_POWER	-2
#define MOVE_SPEED		2

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

Player::Player() : direction(false),
				   animationTimer(0),
				   animationCount(0)
{
}

Player::~Player()
{
}

void Player::init(void)
{
	const int firstPosX = 620;	// ステージファイルからとってくる
	const int firstPosY = 300;

	sprites	= LibSprites::create("player/player.png", 34, 68);
	damageSprites = LibSprites::create("player/player_damage.png", 42, 68);

	sprites -> setPosition(firstPosX, firstPosY);
	sprites -> setAnchorPointY(0.25f);
	damageSprites -> setPosition(firstPosX, firstPosY);

	position.x = firstPosX;
	position.y = firstPosY;
	velocity.x = 0;
	velocity.y = 0;
}

void Player::update(Stage* stage)
{
	LibInput* input = LibInput::getInstance();

	animationTimer++;

	damageSprites -> setDrawFlag(false);
	state = Idle;

	int stageAngle = stage -> getRotateDegree();

	if(stageAngle % 90 == 0)
	{
		if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Left))
		{
			direction = false;
		}
		if(input -> getKeyboardDownState(LibInput::KeyBoardNumber::Key_Right))
		{
			direction = true;
		}

		// 移動
		move(stage);

		// 回転
		sprites -> setRotation(0);
	}
	else
	{
		int quarterDeg = 90;
		int rot = quarterDeg * stage -> getRotateCount() - stageAngle;
		LibDebug::debugMessageLog("------------------------------------------");
		LibDebug::debugMessageLog(string("StageRot : " + to_string(stage -> getRotateCount() - stageAngle)).c_str());
		LibDebug::debugMessageLog(string("Rot : " + to_string(rot)).c_str());

		if(rot > 0)
		{
			if((rot - quarterDeg) < 0)
			{
				LibDebug::debugMessageLog(string("D : 異常 / " + to_string(-rot + quarterDeg)).c_str());
				sprites -> setRotation(-rot + quarterDeg);
			}
			else
			{
				LibDebug::debugMessageLog(string("D : 正常 / " + to_string(rot - quarterDeg)).c_str());
				sprites -> setRotation(rot - quarterDeg);
			}
		}
		else
		{	
			if((rot + quarterDeg) < 0)
			{
				LibDebug::debugMessageLog(string("F : 異常 / " + to_string(-rot - quarterDeg)).c_str());
				sprites -> setRotation(-rot - quarterDeg);
			}
			else
			{
				LibDebug::debugMessageLog(string("F : 正常 / " + to_string(rot + quarterDeg)).c_str());
				sprites -> setRotation(rot + quarterDeg);				
			}
		}
		rotation(rot > 0 ? 1 : -1);

	}

	if(direction)
	{
		sprites -> setScaleX(-1.0f);
	}
	else
	{
		sprites -> setScaleX(1.0f);
	}

	// 描画位置設定
	sprites -> setPosition(position);
	damageSprites -> setPosition(position);
	
	switch(state)
	{
	case Idle:
		if(animationTimer % 10 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap(animationCount, 0, 6);
		break;

	case NoMove:
		animationCount = 6;
		break;

	case Walk:
		if(animationTimer % 5 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap(animationCount, 7, 13);
		break;

	case Fall:
		if(animationTimer % 7 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap(animationCount, 14, 18);
		break;

	case Door:
		if(animationTimer % 7 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap(animationCount, 21, 27);
		break;

	case Damage:
		sprites -> setDrawFlag(false);
		damageSprites -> setDrawFlag(true);
		if(animationTimer % 7 == 0) { animationCount++; }
		animationCount = LibBasicFunc::clamp(animationCount, 0, 6);
		break;
	}
}

void Player::draw(void)
{
	sprites -> draw(animationCount);
	damageSprites -> draw(animationCount);
}

void Player::move(Stage* stage)
{
	// 重力
	velocity.y = GRAVITY_POWER;
	position.y += velocity.y;

	// あたり判定の大きさ
	const int collisionSizeX = sprites -> getTextureSizeX() * sprites -> getAnchorPointX() * 0.9f;
	const int collisionSizeY = sprites -> getTextureSizeY() * sprites -> getAnchorPointY();

	const int upChipNum			= stage -> getChipNumber(position.x, position.y + collisionSizeY + 20);
	const int downLeftChipNum	= stage -> getChipNumber(position.x - collisionSizeX, position.y - collisionSizeY);
	const int downRightChipNum	= stage -> getChipNumber(position.x + collisionSizeX, position.y - collisionSizeY);
	const int leftChipNum		= stage -> getChipNumber(position.x - collisionSizeX, position.y + collisionSizeY);
	const int rightChipNum		= stage -> getChipNumber(position.x + collisionSizeX, position.y + collisionSizeY);

	if(LibInput::getInstance() -> getKeyboardState(LibInput::KeyBoardNumber::Key_Down))
	{
		state = NoMove;
	}

	// 頭上
	if(stage -> getChipNumber(position.x, position.y + collisionSizeY + 20) > 0)
	{
		state = NoMove;
	}

	// 足元
	if(downLeftChipNum > 0 || downRightChipNum > 0)
	{
		int pos = (int)(position.y / collisionSizeY) * collisionSizeY;
		position.y = stage -> getChipPosition(position.x, position.y - collisionSizeY).y + collisionSizeY;

		if(state != NoMove)
		{
			if(LibInput::getInstance() -> getKeyboardState(LibInput::KeyBoardNumber::Key_Left))
			{
				state = Walk;
				velocity.x -= MOVE_SPEED;
				direction = false;
			}
			if(LibInput::getInstance() -> getKeyboardState(LibInput::KeyBoardNumber::Key_Right))
			{
				state = Walk;
				velocity.x += MOVE_SPEED;
				direction = true;
			}
		}
	}
	else
	{
		if(state != NoMove)
		{
			state = Fall;
		}
	}
	
	position.x += velocity.x;

	// 胴体
	if(leftChipNum > 0 || rightChipNum > 0 )
	{
		if(velocity.x == 0)
		{
			if(leftChipNum > 0)
			{
				position.x += collisionSizeX * 0.3f;
			}
			else
			{
				position.x -= collisionSizeX * 0.3f;
			}
		}
		else
		{
			position.x -= velocity.x;
		}
	}

	velocity.x = 0;
	velocity.y = 0;
}