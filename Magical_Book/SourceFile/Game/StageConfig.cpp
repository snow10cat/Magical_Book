
#include "CatGameLib.h"
#include "StageConfig.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static StageConfig* instance = StageConfig::getInstance();


StageConfig::StageConfig() : sizeNumber(Size_S),
							 bgNumber(BG_Castle),
							 musicNumber(BGM_1)
{	
}


StageConfig::~StageConfig()
{
}


void StageConfig::setSizeNumber(SizeNum sizeNum)
{
	sizeNumber = sizeNum;
}

void StageConfig::setBgNumber(BgNum bgNum)
{
	bgNumber = bgNum;
}

void StageConfig::setMusicNumber(MusicNum musicNum)
{
	musicNumber = musicNum;
}

StageConfig::SizeNum StageConfig::getSizeNumber(void)
{
	return sizeNumber;
}

StageConfig::BgNum StageConfig::getBgNumber(void)
{
	return bgNumber;
}

StageConfig::MusicNum StageConfig::getMusicNumber(void)
{
	return musicNumber;
}