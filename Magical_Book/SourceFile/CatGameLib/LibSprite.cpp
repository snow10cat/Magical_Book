
#include "LibSprite.h"

using namespace std;
using namespace CatGameLib;

int LibSprite::loadCount = 0;
unsigned int LibSprite::textureIDs[LoadSpriteMax] = { 0 };

LibSprite* LibSprite::create( const char* fileName)
{
	LibSprite* sprite = new (nothrow)LibSprite();

	if( sprite == nullptr)
	{
		return nullptr;
	}
	sprite -> loadTexture( fileName);
	return sprite;
}

void LibSprite::allRelease( void)
{
	glDeleteTextures( loadCount, textureIDs);
	loadCount = 0;
}

LibSprite::LibSprite() : isRender( true),
						 alpha( 255.0f),
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
	glDeleteTextures( 1, &textureIDs[textureNumber]);
}

void LibSprite::setAlpha( float alpha)
{
	this -> alpha = LibBasicFunc::clamp( alpha, 0.0f, 255.0f);
}

void LibSprite::setAnchorPoint( float pos)
{
	anchor.x = LibBasicFunc::clamp( pos, 0.0f, 1.0f);
	anchor.y = LibBasicFunc::clamp( pos, 0.0f, 1.0f);
}

void LibSprite::setAnchorPoint( float x, float y)
{
	anchor.x = LibBasicFunc::clamp( x, 0.0f, 1.0f);
	anchor.y = LibBasicFunc::clamp( y, 0.0f, 1.0f);
}

void LibSprite::setAnchorPoint( const LibVector2& pos)
{
	anchor.x = LibBasicFunc::clamp( pos.x, 0.0f, 1.0f);
	anchor.y = LibBasicFunc::clamp( pos.y, 0.0f, 1.0f);
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
		pos[i]		+= ( position.x * 2 - screenWidth);
		pos[i + 1]	+= ( position.y * 2 - screenHeight);

		// 拡縮
		pos[i]		*= scale.x;
		pos[i + 1]	*= scale.y;

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
	glBindTexture( GL_TEXTURE_2D, textureIDs[textureNumber]);
	
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

void LibSprite::loadTexture( const char* fileName)
{
	glGenTextures( 1, &textureIDs[loadCount]);

	// 未使用のテクスチャ番号を指定
	glBindTexture( GL_TEXTURE_2D, textureIDs[loadCount]);

	// 指定した番号を保存
	textureNumber = loadCount;

	// カウント更新
	loadCount++;

	// ファイルパス作成
	string filePass = "ResourceFile/Graph/";
	filePass += fileName;

	// png読み込み
	png::image<png::rgba_pixel> image( filePass);

	// 画像サイズ設定
	sizeX = image.get_width();
	sizeY = image.get_height();

	// バッファ確保
	unsigned int* buf = new unsigned int[sizeX * sizeY];

	// 読み込み
	for( int y = 0; y < sizeY; y++)
	{
		for( int x = 0; x < sizeX; x++)
		{
			buf[y * sizeX + x]  = image.get_pixel( x, y).alpha << 24;
			buf[y * sizeX + x] |= image.get_pixel( x, y).blue  << 16;
			buf[y * sizeX + x] |= image.get_pixel( x, y).green << 8;
			buf[y * sizeX + x] |= image.get_pixel( x, y).red;
		}
	}

	// VRAMに転送
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);

	// 転送したテクスチャの設定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// バッファ解放
	delete[] buf;
	buf = nullptr;
}
