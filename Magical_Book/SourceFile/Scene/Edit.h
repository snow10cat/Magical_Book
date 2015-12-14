
#ifndef __MAGICAL_BOOK_EDIT_H__
#define __MAGICAL_BOOK_EDIT_H__

#include "Scene.h"
#include "CatGameLib.h"

namespace MagicalBook
{

class Edit : public Scene
{
public:
	Edit ();
	~Edit ();

	void init(void) override;
	void update(void) override;

	enum EditNumber
	{
		Fadein,			//!< �t�F�[�h�C��
		EditSet,		//!< �G�f�B�b�g���[�h
		BackAnimation,	//!< �O�ɖ߂�A�j���[�V����
		Animation,		//!< ���ɍs���A�j���[�V����
		Next,			//!< ����
	};
	
	

private:

	enum StageSize
	{
		Small	= 14,		//!< S�T�C�Y(�}�b�v�`�b�v14��)
		Medium	= 16,		//!< M�T�C�Y(�}�b�v�`�b�v16��)
		Large	= 18,		//!< L�T�C�Y(�}�b�v�`�b�v18��)
		SizeNum = 3,		
	};

	enum MaterialNum
	{
		Chip,
		Player,
		Enemy,
		Door,
		Gimmick,
		MaterialCount,
	};

	enum EditSelect
	{
		MaterialSelect,
		MaterialSet,
	};

	float volume;		//!< ����
	int volumeFlag;		//!< �Đ��t���O

	int chipCount;
	int chipNum;
	int chipState;
	int chipCounter;
	int chipDirection;
	int chipHave;

	int sizeCounter;
	int bgCounter;
	int bgmCounter;

	int counter;

	int materialRow;		//�s
	int materialCol;		//��
	
	int materialSetRow;		//�s
	int materialSetCol;		//��

	int flag;
	int fadeFlag;
	int bookAnmFlag;
	int anime_number;
	int anime_counter;

	int edit_work;
	int edit_set_work;

	const int sWHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().x / 2;
	const int sHHeaf = CatGameLib::LibMain::getInstance() -> getScreenSize().y / 2;

	CatGameLib::LibInput* input;
	
	CatGameLib::LibSound* editBgm;

	CatGameLib::LibSprite* floor;				//!< ��
	CatGameLib::LibSprites* books;				//!< �{
	
	CatGameLib::LibSprite* materialLogo;		//!< �f�ރ��S
	CatGameLib::LibSprite* chipTable;			//!< �f�ނ�u���t���[��
	CatGameLib::LibSprite* save;				//!< �ۑ�
	CatGameLib::LibSprite* redo;				//!< 1�i��
	CatGameLib::LibSprite* undo;				//!< 1�߂�
	CatGameLib::LibSprite* pointer;				//!< �J�[�\��
	CatGameLib::LibSprite* back;				//!< �߂郍�S

	CatGameLib::LibSprites* materials[5];		//!< �f��

	CatGameLib::LibSprite* gridSize[3];			//!< �O���b�h��
	
	CatGameLib::LibSprites* setMaterials[5];	//!< �z�u�����f��

	CatGameLib::LibSprites* chip;/*
	CatGameLib::LibSprites* player;
	CatGameLib::LibSprites* enemy;
	CatGameLib::LibSprites* gimmick;
	CatGameLib::LibSprites* door;*/
	CatGameLib::LibSprite* music_num[3];
	
	CatGameLib::LibVector2 chipSize;
	CatGameLib::LibVector2 screenSize;
	CatGameLib::LibVector2 stageSize;
	CatGameLib::LibVector2 drawStartingPos;

	std::vector<CatGameLib::LibVector2> chipPosition;
	std::vector<CatGameLib::LibSprite*> bgTextures;

	void pictFade(void);
	void bookAnimation(void);
	void playSound(void);

	void animation(void);
	void edit(void);
	
	void materialSelect(void);
	void materialSet(void);
	
	void editDraw(void);
	void materialDraw(void);
	void editChipSetDraw(void);
	
	void backAnimation(void);
	void fadeout(void);
	void next(void);
};

}

#endif //__MAGICAL_BOOK_EDIT_H__