

#include "ExternalLib.h"
#include "LibSprites.h"

using namespace std;
using namespace CatGameLib;

int LibSprites::allObjectLoadCount = 0;
unsigned int LibSprites::allObjectTextureIDs[LoadSpriteMax * 8] = { 0 };

LibSprites* LibSprites::create( const char* fileName, int width, int height)
{
	LibSprites* sprites = new (nothrow)LibSprites();

	if( sprites == nullptr)
	{
		return nullptr;
	}

	// �t�@�C���p�X�쐬
	string filePass = "ResourceFile/Graph/";
	filePass += fileName;

	// png�ǂݍ���
	png::image<png::rgba_pixel> image( filePass);
	
	int widthCount = image.get_width() / width;
	int heightCount = image.get_height() / height;

	sprites -> spriteCount = widthCount * heightCount;
	sprites -> textureIDArray.resize( sprites -> spriteCount);

	// �摜�T�C�Y�ݒ�
	sprites -> sizeX = width;
	sprites -> sizeY = height;
	
	// �o�b�t�@�m��
	sprites -> pixelBuffer = new unsigned char[width * height * 4];

	for( int y = 0; y < heightCount; y++)
	{
		for( int x = 0; x < widthCount; x++)
		{
			sprites -> createTexture( image, y * widthCount + x, width * x, height * y);
		}
	}

	// �o�b�t�@���
	delete[] sprites -> pixelBuffer;
	sprites -> pixelBuffer = nullptr;

	return sprites;
}

void LibSprites::allRelease( void)
{
	glDeleteTextures( allObjectLoadCount, allObjectTextureIDs);
	allObjectLoadCount = 0;
}

LibSprites::LibSprites() : animationSpeed( 0),
						   animationCount( 0),
						   animationNumber( 0)
{
}

LibSprites::~LibSprites()
{
	glDeleteTextures( textureIDArray.size(), &textureIDArray[0]);
}

void LibSprites::setAnimationSpeed( int speed)
{
	animationSpeed = speed;
}

int LibSprites::getSpriteCount( void)
{
	return spriteCount;
}

void LibSprites::draw( int number)
{
	// �`��t���O�`�F�b�N
	if( !isDraw) { return; }

	drawTexture( textureIDArray[number]);
}

void LibSprites::animation( void)
{
	animationCount++;

	if( animationSpeed != 0)
	{
		if( animationCount % animationSpeed != 0)
		{
			draw( animationNumber);
			return;
		}
	}
	
	animationNumber++;
	animationNumber %= getSpriteCount() - 1;
	
	draw( animationNumber);
}

void LibSprites::createTexture( png::image<png::rgba_pixel>& image, int number, int posX, int posY)
{
	glGenTextures( 1, &textureIDArray[number]);

	// ���g�p�̃e�N�X�`���ԍ����w��
	glBindTexture( GL_TEXTURE_2D, textureIDArray[number]);

	allObjectTextureIDs[allObjectLoadCount] = textureIDArray[number];

	// �J�E���g�X�V
	allObjectLoadCount++;

	// �ǂݍ���
	for( int y = 0; y < sizeY; y++)
	{
		memcpy( &pixelBuffer[sizeX * y * 4], &image[posY + y][posX], sizeX * 4);
	}

	// VRAM�ɓ]��
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);

	// �]�������e�N�X�`���̐ݒ�
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
