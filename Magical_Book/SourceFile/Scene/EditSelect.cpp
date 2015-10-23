
#include "../Game/ResourceManager.h"
#include "CatGameLib.h"
#include "SceneManager.h"
#include "EditSelect.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


static ResourceManager* instance = ResourceManager::getInstance();


EditSelect::EditSelect() : size_section(nullptr),
						   bg_section(nullptr),
						   music_section(nullptr)
{
	size_section = CatGameLib::LibSprite::create( "logo/size_section.png");
	bg_section = CatGameLib::LibSprite::create( "logo/bg_section.png");
	music_section = CatGameLib::LibSprite::create( "logo/music_section.png");
	bgm_logo[0] = CatGameLib::LibSprite::create( "logo/bgm1.png");
	bgm_logo[1] = CatGameLib::LibSprite::create( "logo/bgm2.png");
	bgm_logo[2] = CatGameLib::LibSprite::create( "logo/bgm3.png");
}


EditSelect::~EditSelect()
{
}


void EditSelect::init( void)
{
	instance -> getSprites("books") -> setPosition(sWHeaf - 320, sHHeaf);
	instance -> getSprites("books") -> setScale(1.5f);

	bgm_logo[0] -> setPosition(sWHeaf - 100, sHHeaf - 210);
	bgm_logo[0] -> setScale(0.3f);
	bgm_logo[0] -> setAlpha(0.0f);

	bgm_logo[1] -> setPosition(sWHeaf + 50, sHHeaf - 210);
	bgm_logo[1] -> setScale(0.25f);
	bgm_logo[1] -> setAlpha(0.0f);

	bgm_logo[2] -> setPosition(sWHeaf + 200, sHHeaf - 210);
	bgm_logo[2] -> setScale(0.25f);
	bgm_logo[2] -> setAlpha(0.0f);

	for( int i = 1; i <= ResourceManager::BG_Count; i++)
	{
		string bgName = "game_bg" + to_string(i);
		bgTextures.push_back( instance -> getSprite( bgName.c_str()));
		bgTextures[i - 1] -> setAlpha(0.0f);
	}

	bgTextures[ResourceManager::BG_Castle] -> setPosition(sWHeaf - 100, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Castle] -> setScale(0.17f);

	bgTextures[ResourceManager::BG_Table] -> setPosition(sWHeaf - 25, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Table] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Gate] -> setPosition(sWHeaf + 50, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Gate] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Window] -> setPosition(sWHeaf + 125, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Window] -> setScale(0.1f);

	bgTextures[ResourceManager::BG_Throne] -> setPosition(sWHeaf + 200, sHHeaf - 30);
	bgTextures[ResourceManager::BG_Throne] -> setScale(0.1f);

	instance ->getSprite("frame") -> setPosition(sWHeaf - 210, sHHeaf + 160);
	instance ->getSprite("frame") -> setScale(0.35f);
	instance ->getSprite("frame") -> setAlpha(0.0f);

	size_section -> setPosition(sWHeaf - 100, sHHeaf + 300);
	size_section -> setScale( 0.8f);
	
	bg_section -> setPosition(sWHeaf - 100, sHHeaf + 80);
	bg_section -> setScale( 0.7f);

	music_section -> setPosition(sWHeaf - 100, sHHeaf - 140);
	music_section -> setScale( 0.7f);

	timer = 0;
	counter = 0;
	flag = 0;
	fadeFlag = 0;
	bookAnmFlag = 0;
	anime_number = BOOK_ANM_MIN;
	anime_counter = 0;
	Volume = 0;

//	select_work = ModeSelect;
}


void EditSelect::update( void)
{
	instance -> getSprite("floar") -> draw();
	instance -> getSprites("books") -> draw(anime_number);
	size_section -> draw();
	bg_section -> draw();
	music_section -> draw();

	for(int i = 0; i <= 2; i++)
	{
		if(bgm_logo[i] -> getAlpha() < 255)
		{
			bgm_logo[i] -> setAlpha(bgm_logo[i] -> getAlpha() + 5);
		}	
		bgm_logo[i] -> draw();
	}

	if( instance ->getSprite("frame") -> getAlpha() < 255)
	{
		instance ->getSprite("frame") -> setAlpha(instance ->getSprite("frame") -> getAlpha() + 5);
	}
	instance ->getSprite("frame") -> draw();

	auto sizeResetFunc = [&](void)
	{
		instance -> getSprite("game_bg1") -> setScale(0.1f);
		instance -> getSprite("game_bg2") -> setScale(0.1f);
		instance -> getSprite("game_bg3") -> setScale(0.1f);
		instance -> getSprite("game_bg4") -> setScale(0.1f);
		instance -> getSprite("game_bg5") -> setScale(0.1f);
	};


	for( int i = 0; i < bgTextures.size(); i++)
	{
		bgTextures[i] -> draw();

		if(bgTextures[i] -> getAlpha() < 255)
		{
			bgTextures[i] -> setAlpha(bgTextures[i] -> getAlpha() + 5);
		}
	}
}