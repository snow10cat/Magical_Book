
#include "CatGameLib.h"
#include "ExternalLib.h"

using namespace std;
using namespace CatGameLib;

int LibSprite::loadCount = 0;
unsigned int LibSprite::textureIDs[LoadSpriteMax] = { 0 };

LibSprite::LibSprite() : alpha( 255.0f),
						 sizeX( 0.0f),
						 sizeY( 0.0f),
						 angle( 0.0f),
						 position( 0.0f, 0.0f),
						 scale( 1.0f, 1.0f),
						 anchor( 0.0f, 0.0f)
{
}

LibSprite::~LibSprite()
{
}

LibSprite* LibSprite::create( const char* fileName)
{
	LibSprite* sprite( new LibSprite());

	if( sprite == nullptr)
	{
		return nullptr;
	}
	sprite -> loadTexture( fileName);
	return sprite;
}

void LibSprite::setAlpha( float alpha)
{
	this -> alpha = LibBaseFunc::clamp( alpha, 0.0f, 255.0f);
}

void LibSprite::setPosition( float x, float y)
{
	position.x = x;
	position.y = y;
}

void LibSprite::setPosition( const LibVector2& pos)
{
	position = pos;
}

void LibSprite::setRotation( int angle)
{
	this -> angle = angle;
}

void LibSprite::setRotation( float angle)
{
	this -> angle = angle;
}

void LibSprite::setScale( float scale)
{
	this -> scale.x = scale;
	this -> scale.y = scale;
}

void LibSprite::setScale( float x, float y)
{
	scale.x = x;
	scale.y = y;
}

void LibSprite::setScale( const LibVector2& scale)
{
	this -> scale = scale;
}

void LibSprite::draw( void)
{
	glBindTexture( GL_TEXTURE_2D, textureIDs[textureNumber]);

	LibMain* libMain = LibMain::getInstance();

	LibVector2 worldPos = libMain -> screenPosToWorldPos( position);

	LibVector2 worldSize;
	worldSize.x = ( sizeX / libMain -> getScreenSize().x);
	worldSize.y = ( sizeY / libMain -> getScreenSize().y);

	GLfloat pos[] = {
		( worldPos.x - worldSize.x) * scale.x, ( worldPos.y + worldSize.y) * scale.y,	// 左上
		( worldPos.x - worldSize.x) * scale.x, ( worldPos.y - worldSize.y) * scale.y,	// 左下
		( worldPos.x + worldSize.x) * scale.x, ( worldPos.y + worldSize.y) * scale.y,	// 右上
		( worldPos.x + worldSize.x) * scale.x, ( worldPos.y - worldSize.y) * scale.y,	// 右下
	};

	const GLfloat uv[] = {
		0, 0,
		0, 1,
		1, 0,
		1, 1,
	};

	if( angle.getRadian() != 0.0f)
	{
		float sin_f = sinf( angle.getRadian());
		float cos_f = cosf( angle.getRadian());

		for( int i = 0; i < 8; i += 2)
		{
			float dx = pos[i];
			float dy = pos[i + 1];

			pos[i] = (float)( dx * cos_f - dy * sin_f) + worldSize.x;
			pos[i + 1] = (float)( dx * sin_f + dy * cos_f) + worldSize.y;
		}
	}

	if( alpha < 255.0f)
	{
		glEnable( GL_BLEND);
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniform1f( LibMain::getInstance() -> getNowShader() -> getUniformHandle( "alpha"), alpha);
	}

	glVertexAttribPointer( LibMain::getInstance() -> getNowShader() -> getAttributePosition(), 2, GL_FLOAT, false, 0, pos);
	glVertexAttribPointer( LibMain::getInstance() -> getNowShader() -> getAttributeUV(), 2, GL_FLOAT, false, 0, uv);
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4);
	glDisable( GL_BLEND);
}

void LibSprite::loadTexture( const char* fileName)
{
	glBindTexture( GL_TEXTURE_2D, textureIDs[loadCount]);
	textureNumber = loadCount;
	loadCount++;

	string filePass = "ResourceFile/Graph/";
	filePass += fileName;

	png::image<png::rgba_pixel> image( filePass);
	sizeX = image.get_width();
	sizeY = image.get_height();

	unsigned int* data = new unsigned int[sizeX * sizeY];

	for( int y = 0; y < sizeY; y++)
	{
		for( int x = 0; x < sizeX; x++)
		{
			data[y * sizeX + x]  = image.get_pixel( x, y).alpha << 24;
			data[y * sizeX + x] |= image.get_pixel( x, y).green << 8;
			data[y * sizeX + x] |= image.get_pixel( x, y).blue	<< 16;
			data[y * sizeX + x] |= image.get_pixel( x, y).red;
		}
	}

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	delete[] data;
	data = nullptr;
}
