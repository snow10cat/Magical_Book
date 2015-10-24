
#include "Player.h"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

Player::Player() : direction( false),
				   animationTimer( 0),
				   animationCount( 0)
{
}

Player::~Player()
{
}

void Player::init( void)
{
	const int firstPosX = 620;	// ステージファイルからとってくる
	const int firstPosY = 360;

	sprites	= LibSprites::create( "player/player.png", 34, 68);
	damageSprites = LibSprites::create( "player/player_damage.png", 42, 68);

	sprites -> setPosition( firstPosX, firstPosY);
	damageSprites -> setPosition( firstPosX, firstPosY);

	position.x = firstPosX;
	position.y = firstPosY;
	velocity.x = 0;
	velocity.y = 0;
}

void Player::update( Stage* stage)
{
	LibInput* input = LibInput::getInstance();

	animationTimer++;

	damageSprites -> setDrawFlag( false);
	state = Idle;

	if( input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Left))
	{
		if( direction)
		{
			sprites -> setScaleX( -sprites -> getScaleX());
			direction = false;
		}
	}

	if( input -> getKeyboardDownState( LibInput::KeyBoardNumber::Key_Right))
	{
		if( !direction)
		{
			sprites -> setScaleX( -sprites -> getScaleX());
			direction = true;
		}
	}

	int stageAngle = stage -> getRotateDegree();
	if( stageAngle % 90 == 0)
	{
		if( input -> getKeyboardState( LibInput::KeyBoardNumber::Key_Left))
		{
			state = Walk;
			velocity.x -= 1;
		}
		if( input -> getKeyboardState( LibInput::KeyBoardNumber::Key_Right))
		{
			state = Walk;
			velocity.x += 1;
		}

		// 重力
		velocity.y = -1;

		// 移動
		move( stage);
	}
	rotation( stage);
	
	// 描画位置設定
	sprites -> setPosition( position);
	damageSprites -> setPosition( position);
	
	switch( state)
	{
	case Idle:
		if( animationTimer % 10 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap( animationCount, 0, 6);
		break;

	case NoMove:
		animationCount = 6;
		break;

	case Walk:
		if( animationTimer % 5 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap( animationCount, 7, 13);
		break;

	case Fall:
		if( animationTimer % 4 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap( animationCount, 14, 18);
		break;

	case Door:
		if( animationTimer % 7 == 0) { animationCount++; }
		animationCount = LibBasicFunc::wrap( animationCount, 21, 27);
		break;

	case Damage:
		sprites -> setDrawFlag( false);
		damageSprites -> setDrawFlag( true);
		if( animationTimer % 7 == 0) { animationCount++; }
		animationCount = LibBasicFunc::clamp( animationCount, 0, 6);
		break;
	}
}

void Player::draw( void)
{
	sprites -> draw( animationCount);
	damageSprites -> draw( animationCount);
}

void Player::move( Stage* stage)
{
	position.x += velocity.x;
	position.y += velocity.y;

	// 足元
	if( stage -> getChipNumbr( position.x, position.y - sprites -> getTextureSizeY() / 2) > 0)
	{
		position.y -= velocity.y;
	}
	else
	{
		state = Fall;
	}
	
	// 頭上
	if( stage -> getChipNumbr( position.x, position.y + 20) > 0)
	{
		position.y -= velocity.y;
		if( state != Fall)
		{
			state = NoMove;
		}
	}

	// 胴体
	if( stage -> getChipNumbr( position.x - sprites -> getTextureSizeX() / 2, position.y) > 0 ||
		stage -> getChipNumbr( position.x + sprites -> getTextureSizeX() / 2, position.y) > 0 )
	{
		position.x -= velocity.x;
	}

	// 頭部 (それっぽい位置)
	if( stage -> getChipNumbr( position.x - sprites -> getTextureSizeX() / 2, position.y + 20) > 0 ||
		stage -> getChipNumbr( position.x + sprites -> getTextureSizeX() / 2, position.y + 20) > 0 )
	{
		position.x -= velocity.x;
	}

	velocity.x = 0;
	velocity.y = 0;
}