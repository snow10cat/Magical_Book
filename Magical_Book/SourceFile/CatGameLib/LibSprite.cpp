
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
						 anchor( 0.5f, 0.5f)
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
	// renderflag

	glBindTexture( GL_TEXTURE_2D, textureIDs[textureNumber]);

	LibMain*	libMain		= LibMain::getInstance();
	LibShader*	libShader	= libMain -> getNowShader();

	LibVector2	worldPos	= libMain -> screenPosToWorldPos( position);

	LibVector2 worldSize;
	worldSize.x = ( sizeX * scale.x / libMain -> getScreenSize().x) * 0.5f;
	worldSize.y = ( sizeY * scale.y / libMain -> getScreenSize().y) * 0.5f;

	LibVector2 worldAnchor;
	worldAnchor.x = worldSize.x * ( anchor.x * 2 - 1);
	worldAnchor.y = worldSize.y * ( anchor.y * 2 - 1);

	GLfloat pos[] = {
		( -worldSize.x - worldAnchor.x),  ( worldSize.y - worldAnchor.y),	// 左上
		( -worldSize.x - worldAnchor.x), ( -worldSize.y - worldAnchor.y),	// 左下
		( worldSize.x - worldAnchor.x),  ( worldSize.y - worldAnchor.y),	// 右上
		( worldSize.x - worldAnchor.x), ( -worldSize.y - worldAnchor.y),	// 右下
	};

	const GLfloat uv[] = {
		0, 0,
		0, 1,
		1, 0,
		1, 1,
	};

	const float axis_x = 0.0f;
	const float axis_y = 0.0f;
	const float axis_z = 1.0f;

	const float sin_f = sinf( angle.getRadian());
	const float cos_f = cosf( angle.getRadian());

	GLfloat move[4][4] = { 0 };

	move[3][0] = worldPos.x;
	move[3][1] = worldPos.y;
	move[3][3] = 1.0f;

	GLfloat rot[4][4] = {
		  ( axis_x * axis_x) * ( 1.0f - cos_f) + cos_f, 
		  ( axis_x * axis_y) * ( 1.0f - cos_f) - axis_z * sin_f, 
		  ( axis_x * axis_z) * ( 1.0f - cos_f) + axis_y * sin_f, 
		  0,
		  ( axis_y * axis_x) * ( 1.0f - cos_f) + axis_z * sin_f, 
		  ( axis_y * axis_y) * ( 1.0f - cos_f) + cos_f, 
		  ( axis_y * axis_z) * ( 1.0f - cos_f) - axis_x * sin_f, 
		  0,
		  ( axis_z * axis_x) * ( 1.0f - cos_f) - axis_y * sin_f, 
		  ( axis_z * axis_y) * ( 1.0f - cos_f) + axis_x * sin_f, 
		  ( axis_z * axis_z) * ( 1.0f - cos_f) + cos_f, 
		  0,
		  0,
		  0,
		  0,
		  1
	};

	GLfloat _scale[4][4] = { 0 };

	_scale[0][0] = scale.x;
	_scale[1][1] = scale.y;


	glUniformMatrix4fv( libShader -> getUniformHandle( "unif_translate"), 1, GL_FALSE, move[0]);
	glUniformMatrix4fv( libShader -> getUniformHandle( "unif_rotate"), 1, GL_FALSE, rot[0]);
	glUniformMatrix4fv( libShader -> getUniformHandle( "unif_scale"), 1, GL_FALSE, _scale[0]);

	glEnable( GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniform1f( libShader -> getUniformHandle( "alpha"), alpha / 255.0f);

	glVertexAttribPointer( libShader -> getAttributePosition(), 2, GL_FLOAT, false, 0, pos);
	glVertexAttribPointer( libShader -> getAttributeUV(), 2, GL_FLOAT, false, 0, uv);
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
