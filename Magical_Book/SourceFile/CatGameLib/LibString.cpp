
#include "LibString.h"

#define DEBUG_FONT_DIR "../../SourceFile/CatGameLib/DebugFont/dbgfont.png"

using namespace std;
using namespace CatGameLib;

LibSprites* LibString::sprites = nullptr;

LibString* LibString::create( const char* message)
{
	LibString* instance = new (nothrow)LibString();
	if( instance == nullptr)
	{
		return nullptr;
	}

	instance -> message = message;
	return instance;
}

void LibString::loadTexture( void)
{
	if( sprites) { return; }
	sprites = LibSprites::create( DEBUG_FONT_DIR, 32, 32);
}

LibString::LibString()
{
}

LibString::~LibString()
{
}

void LibString::setString( const char* message)
{
	this -> message = message;
}

void LibString::draw( void)
{
	const int	messageCount = message.size();					// 文字数
	const float textureSizeX = sprites -> getTextureSizeX();	// 文字テクスチャの大きさ
	const float intervalX	 = textureSizeX * getScaleX();		// 文字の間隔

	sprites -> setAnchorPoint( getAnchorPoint());
	sprites -> setRotation( getRotationRadian());
	sprites -> setScale( getScale());

	for( int i = 0; i < messageCount; i++)
	{
		const float basePosX = getPositionX() - ( textureSizeX * ( messageCount - 1) * anchor.x);

		sprites -> setPosition( basePosX + intervalX * i, getPositionY());
		sprites -> draw( message.c_str()[i]);
		sprites -> setPositionX( getPositionX());
	}
}