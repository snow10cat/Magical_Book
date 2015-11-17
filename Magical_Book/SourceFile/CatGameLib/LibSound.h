
#ifndef __CAT_GAME_LIBRARY_SOUND_H__
#define __CAT_GAME_LIBRARY_SOUND_H__

namespace CatGameLib
{

class LibSound
{
public:
	enum SoundState
	{
		Play,
		Pause,
		Stop,
		Init,
	};

	static LibSound* create(const char* fileName);
	static void allRelease(void);
	static void allStop(void);

	void setLoop(bool isLoop);
	void setVolume(float vol);

	SoundState getState(void);

	void play(void);
	void pause(void);
	void stop(void);
	void restart(void);

private:
	enum
	{
		LoadSoundMax = 1024,
	};
	static int loadCount;
	static unsigned int sourceIDs[LoadSoundMax];
	static unsigned int bufferIDs[LoadSoundMax];

	unsigned int sourceID;
	unsigned int bufferID;

	LibSound();
	~LibSound();

	void loadFile(const char* fileName);
};

}

#endif // __CAT_GAME_LIBRARY_SOUND_H__