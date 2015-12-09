
#ifndef __MAGICAL_BOOK_RESOURCE_MANEGER_H__
#define __MAGICAL_BOOK_RESOURCE_MANEGER_H__

#include "CatGameLib.h"
#include "ExternalLib.h"


#define MAX_VOLUME 1.0f			//!< �ő剹��
#define BGM_FADE 0.02f			//!< ���y�t�F�[�h���Z�l
#define DEFAULT_SIZE 1.0f		//!< �����T�C�Y
#define FADE 10					//!< �t�F�[�h���Z�l

#define BOOK_POS_X 300			//!< ��ʒ��S����ʒu���������l(�J���Ă���{�̈ʒu)
#define TITLE_BOOK_POS_X 250	//!< ��ʒ��S����ʒu���������l(�^�C�g���̖{�ʒu)
#define EDIT_SEL_BOOK_POS_X 320	//!< ��ʒ��S����ʒu���������l(�G�f�B�b�g�I���̖{�ʒu)
#define EDIT_BOOK_POS_X 200		//!< ��ʒ��S����ʒu���������l(�G�f�B�b�g�̖{�ʒu)
#define MOVEMENT_BOOK 10		//!< �{�̈ړ����x
#define BOOK_ANIM_SPEED 7		//!< �{�̃A�j���[�V�������x


namespace MagicalBook
{

class ResourceManager
{
public:
	enum Size
	{
		Size_S,						//!< S�T�C�Y
		Size_M,						//!< M�T�C�Y
		Size_L,						//!< L�T�C�Y
		Size_Count = Size_L + 1,	//!< �T�C�Y�̐�
	};

	enum BgName
	{
		BG_Castle,					//!< �w�i(��O)
		BG_Table,					//!< �w�i(��)
		BG_Gate,					//!< �w�i(��)
		BG_Window,					//!< �w�i(��)
		BG_Throne,					//!< �w�i(�ʍ�)
		BG_Count = BG_Throne + 1,	//!< �w�i�̐�
	};

	enum BgmNum
	{
		BGM_1,						//!< ���y1
		BGM_2,						//!< ���y2
		BGM_3,						//!< ���y3
		BGM_Count = BGM_3 + 1,		//!< ���y�̐�
	};

	static ResourceManager* getInstance(void)
	{
		static ResourceManager* instance = nullptr;
		if(!instance) {instance = new ResourceManager();}
		return instance;
	}
	ResourceManager(const ResourceManager&) = delete;

	const ResourceManager& operator=(const ResourceManager&) = delete;

	void loadResource(void);

	CatGameLib::LibSound* getSound(const std::string& fileName);

	CatGameLib::LibSprite* getSprite(const std::string& fileName);
	CatGameLib::LibSprites* getSprites(const std::string& fileName);

private:

	ResourceManager();
	~ResourceManager();

	std::map<std::string, CatGameLib::LibSound*> soundArray;

	std::map<std::string, CatGameLib::LibSprite*> spriteArray;
	std::map<std::string, CatGameLib::LibSprites*> spritesArray;
};

}

#endif // __MAGICAL_BOOK_SPRITE_MANEGER_H__


