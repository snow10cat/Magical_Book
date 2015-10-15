
#include "CatGameLib.h"
#include "ExternalLib.h"

#include "LibSound.h"

using namespace std;
using namespace CatGameLib;

int LibSound::loadCount = 0;
unsigned int LibSound::sourceIDs[LoadSoundMax] = { 0 };
unsigned int LibSound::bufferIDs[LoadSoundMax] = { 0 };

LibSound* LibSound::create( const char* fileName)
{
	LibSound* sound = new (nothrow)LibSound();

	if( sound == nullptr)
	{
		return nullptr;
	}

	sound -> loadFile( fileName);
	return sound;
}

void LibSound::allRelease( void)
{
	alSourceStopv( loadCount, sourceIDs);
	alDeleteSources( loadCount, sourceIDs);
	alDeleteBuffers( loadCount, bufferIDs);
	loadCount = 0;
}

LibSound::LibSound() : sourceID( 0),
					   bufferID( 0)
{
}

LibSound::~LibSound()
{
	stop();
	alDeleteSources( 1, &sourceIDs[sourceID]);
	alDeleteBuffers( 1, &bufferIDs[bufferID]);
}

void LibSound::setLoop( bool isLoop)
{
	alSourcei( sourceIDs[sourceID], AL_LOOPING, isLoop);
}

void LibSound::setVolume( float vol)
{
	alSourcef( sourceIDs[sourceID], AL_GAIN, LibBasicFunc::clamp( vol, 0.0f, 1.0f));
}

void LibSound::play( void)
{
	alSourcePlay( sourceIDs[sourceID]);
}

void LibSound::pause( void)
{
	alSourcePause( sourceIDs[sourceID]);
}

void LibSound::stop( void)
{
	alSourceStop( sourceIDs[sourceID]);
}

void LibSound::restart( void)
{
	stop();
	play();
}

void LibSound::loadFile( const char* fileName)
{
	string filePass = "ResourceFile/Sound/";
	filePass += fileName;

	// �\�[�X�쐬
	alGenSources( 1, &sourceIDs[loadCount]);

	// �o�b�t�@�쐬
	bufferIDs[loadCount] = alureCreateBufferFromFile( filePass.c_str());
	if( bufferIDs[loadCount] == AL_NONE) 
	{
		string message = "can't load from ";
		message += fileName;
		LibDebug::errorMessageBox( message.c_str());
	}

	// �w�肵���ԍ���ۑ�
	sourceID = loadCount;
	bufferID = loadCount;

	// �J�E���g�X�V
	loadCount++;

	// �o�b�t�@�������ɐݒ�
	alSourcei( sourceIDs[sourceID], AL_BUFFER, bufferIDs[bufferID]);

	// ���ʂ𔼕���
	alSourcef( sourceIDs[sourceID], AL_GAIN, 0.5f);
}
	