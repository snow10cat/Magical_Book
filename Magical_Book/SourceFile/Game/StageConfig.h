
#ifndef __MAGICAL_BOOK_STAGE_CONFIG_H__
#define __MAGICAL_BOOK_STAGE_CONFIG_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace MagicalBook
{

class StageConfig
{
public:

	enum SizeNum
	{
		Size_S,
		Size_M,
		Size_L,
	};

	enum BgNum
	{
		BG_Castle,
		BG_Table,
		BG_Gate,
		BG_Window,
		BG_Throne,
	};

	enum MusicNum
	{
		BGM_1,
		BGM_2,
		BGM_3,
	};

	static StageConfig* getInstance(void)
	{
		static StageConfig* instance = nullptr;
		if(!instance) {instance = new StageConfig();}
		return instance;
	}
	StageConfig(const StageConfig&) = delete;
	const StageConfig& operator=(const StageConfig&) = delete;

	void setSizeNumber(SizeNum sizeNum);
	void setBgNumber(BgNum bgNum);
	void setMusicNumber(MusicNum musicNum);

	SizeNum getSizeNumber(void);
	BgNum getBgNumber(void);
	MusicNum getMusicNumber(void);

private:
	SizeNum sizeNumber;
	BgNum bgNumber;
	MusicNum musicNumber;


	StageConfig();
	~StageConfig();

};

}

#endif // __MAGICAL_BOOK_STAGE_CONFIG_H__


