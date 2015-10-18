
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

void LibSound::allStop( void)
{
	alSourceStopv( loadCount, sourceIDs);
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

	// ソース作成
	alGenSources( 1, &sourceIDs[loadCount]);

	// バッファ作成
	bufferIDs[loadCount] = alureCreateBufferFromFile( filePass.c_str());
	if( bufferIDs[loadCount] == AL_NONE) 
	{
		string message = "can't load from ";
		message += fileName;
		LibDebug::errorMessageBox( message.c_str());
	}

	// 指定した番号を保存
	sourceID = loadCount;
	bufferID = loadCount;

	// カウント更新
	loadCount++;

	// バッファを音源に設定
	alSourcei( sourceIDs[sourceID], AL_BUFFER, bufferIDs[bufferID]);

	// 音量を半分に
	alSourcef( sourceIDs[sourceID], AL_GAIN, 0.5f);
}
	