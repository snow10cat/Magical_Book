
#include "LibSprites.h"

using namespace std;
using namespace CatGameLib;

int LibSprites::loadCount = 0;
unsigned int LibSprites::allObjectTextureIDs[LoadSpriteMax] = { 0 };

LibSprites* LibSprites::create( const char* fileName, int width, int height)
{
	LibSprites* sprites = new (nothrow)LibSprites();

	if( sprites == nullptr)
	{
		return nullptr;
	}

	// ファイルパス作成
	string filePass = "ResourceFile/Graph/";
	filePass += fileName;

	// png読み込み
	png::image<png::rgba_pixel> image( filePass);

	int widthCount = image.get_width() / width;
	int heightCount = image.get_height() / height;

	sprites -> spriteCount = widthCount + heightCount;
	sprites -> textureIDs.resize( sprites -> spriteCount);

	// 画像サイズ設定
	sprites -> sizeX = width;
	sprites -> sizeY = height;
	
	// バッファ確保
	sprites -> pixelBuffer = new unsigned int[image.get_width() * image.get_height()];
	
	for( int y = 0; y < heightCount; y++)
	{
		for( int x = 0; x < widthCount; x++)
		{
			sprites -> createTexture( image, y + x, width * x, height * y);
		}
	}

	// バッファ解放
	delete[] sprites -> pixelBuffer;
	sprites -> pixelBuffer = nullptr;

	return sprites;
}

void LibSprites::allRelease( void)
{
	glDeleteTextures( loadCount, allObjectTextureIDs);
	loadCount = 0;
}

LibSprites::LibSprites() : animationSpeed( 0),
						   animationCount( 0),
						   animationNumber( 0),
						   isRender( true),
						   alpha( 255.0f),
						   sizeX( 0.0f),
						   sizeY( 0.0f),
						   angle( 0.0f),
						   position( 0.0f, 0.0f),
						   scale( 1.0f, 1.0f),
						   anchor( 0.5f, 0.5f)
{
}

LibSprites::~LibSprites()
{
	glDeleteTextures( textureIDs.size(), &textureIDs[0]);
}

void LibSprites::setAlpha( float alpha)
{
	this -> alpha = LibBasicFunc::clamp( alpha, 0.0f, 255.0f);
}

void LibSprites::setAnimationSpeed( int speed)
{
	animationSpeed = speed;
}

void LibSprites::setAnchorPoint( float pos)
{
	anchor.x = LibBasicFunc::clamp( pos, 0.0f, 1.0f);
	anchor.y = LibBasicFunc::clamp( pos, 0.0f, 1.0f);
}

void LibSprites::setAnchorPoint( float x, float y)
{
	anchor.x = LibBasicFunc::clamp( x, 0.0f, 1.0f);
	anchor.y = LibBasicFunc::clamp( y, 0.0f, 1.0f);
}

void LibSprites::setAnchorPoint( const LibVector2& pos)
{
	anchor.x = LibBasicFunc::clamp( pos.x, 0.0f, 1.0f);
	anchor.y = LibBasicFunc::clamp( pos.y, 0.0f, 1.0f);
}

void LibSprites::setPosition( float x, float y)
{
	position.x = x;
	position.y = y;
}

void LibSprites::setPosition( const LibVector2& pos)
{
	position = pos;
}

void LibSprites::setRotation( int angle)
{
	this -> angle = angle;
}

void LibSprites::setRotation( float angle)
{
	this -> angle = angle;
}

void LibSprites::setScale( float scale)
{
	this -> scale.x = scale;
	this -> scale.y = scale;
}

void LibSprites::setScale( float x, float y)
{
	scale.x = x;
	scale.y = y;
}

void LibSprites::setScale( const LibVector2& scale)
{
	this -> scale = scale;
}

float LibSprites::getAlpha( void)
{
	return alpha;
}
		 
int LibSprites::getAnimationSpeed( void)
{
	return animationSpeed;
}
		 
float LibSprites::getAnchorPointX( void)
{
	return anchor.x;
}

float LibSprites::getAnchorPointY( void)
{
	return anchor.y;
}

LibVector2 LibSprites::getAnchorPoint( void)
{
	return anchor;
}
		 
float LibSprites::getPositionX( void)
{
	return position.x;
}

float LibSprites::getPositionY( void)
{
	return position.y;
}

LibVector2 LibSprites::getPosition( void)
{
	return position;
}
		 
int LibSprites::getRotationDegree( void)
{
	return angle.getDegree();
}

float LibSprites::getRotationRadian( void)
{
	return angle.getRadian();
}

float LibSprites::getScaleX( void)
{
	return scale.x;
}

float LibSprites::getScaleY( void)
{
	return scale.y;
}

LibVector2 LibSprites::getScale( void)
{
	return scale;
}

int LibSprites::getSpriteCount( void)
{
	return spriteCount;
}

void LibSprites::draw( int number)
{
	// 描画フラグチェック
	if( !isRender) { return; }

	LibMain* libMain = LibMain::getInstance();

	// 画像サイズとアンカーポイントから4点を生成
	float w = sizeX * anchor.x;
	float h = sizeY * anchor.y;
	GLfloat pos[] = {
		-w,			sizeY - h,
		-w,		   -h,
		 sizeX - w,  sizeY - h,
		 sizeX - w, -h,
	};

	float sin_f = sinf( -angle.getRadian());
	float cos_f = cosf( -angle.getRadian());
	float screenWidth = libMain -> getScreenSize().x;
	float screenHeight = libMain -> getScreenSize().y;

	for( int i = 0; i < 8; i += 2)
	{
		float dx = pos[i];
		float dy = pos[i + 1];

		// 回転
		pos[i]		= dx * cos_f - dy * sin_f;
		pos[i + 1]	= dx * sin_f + dy * cos_f;

		// 移動
		pos[i]		+= ( position.x - screenWidth * 0.5f);
		pos[i + 1]	+= ( position.y - screenHeight * 0.5f);

		// 拡縮
		pos[i]		*= scale.x * 2;
		pos[i + 1]	*= scale.y * 2;

		// ワールド変換
		pos[i]		= pos[i] / screenWidth;
		pos[i + 1]	= pos[i + 1] / screenHeight;

	}

	// UV座標
	const GLfloat uv[] = {
		0, 0,
		0, 1,
		1, 0,
		1, 1,
	};

	// テクスチャ設定
	glBindTexture( GL_TEXTURE_2D, textureIDs[number]);
	
	// アルファブレンドON
	glEnable( GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// シェーダーのUniformにアルファ値を転送
	glUniform1f( LibMain::getInstance() -> getNowShader() -> getUniformHandle( "alpha"), alpha / 255.0f);

	// シェーダーに画像の座標を転送
	glVertexAttribPointer( LibMain::getInstance() -> getNowShader() -> getAttributePosition(), 2, GL_FLOAT, false, 0, pos);
	
	// シェーダーにUV座標を転送
	glVertexAttribPointer( LibMain::getInstance() -> getNowShader() -> getAttributeUV(), 2, GL_FLOAT, false, 0, uv);
	
	// 描画
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4);
	
	// アルファブレンドOFF
	glDisable( GL_BLEND);
}

void LibSprites::animation( void)
{
	animationCount++;

	if( animationCount % animationSpeed == 0)
	{
		animationNumber++;
		animationNumber %= getSpriteCount() - 1;
	}

	draw( animationNumber);
}

void LibSprites::createTexture( png::image<png::rgba_pixel>& image, int number, int posX, int posY)
{
	glGenTextures( 1, &textureIDs[number]);

	// 未使用のテクスチャ番号を指定
	glBindTexture( GL_TEXTURE_2D, textureIDs[number]);

	allObjectTextureIDs[loadCount] = textureIDs[number];

	// カウント更新
	loadCount++;

	// 読み込み
	for( int y = posY; y < sizeY + posY; y++)
	{
		for( int x = posX; x < sizeX + posX; x++)
		{
			pixelBuffer[y * sizeX + x]  = image.get_pixel( x, y).alpha << 24;
			pixelBuffer[y * sizeX + x] |= image.get_pixel( x, y).blue  << 16;
			pixelBuffer[y * sizeX + x] |= image.get_pixel( x, y).green << 8;
			pixelBuffer[y * sizeX + x] |= image.get_pixel( x, y).red;
		}
	}

	// VRAMに転送
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);

	// 転送したテクスチャの設定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
