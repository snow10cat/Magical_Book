
#include "SceneManager.h"
#include "Title.h"
#include "MenuSelect.h"
#include "Stageselect.h"
#include "EditSelect.h"
#include "Game.h"
#include "Edit.h"


using namespace MagicalBook;

SceneManager::SceneManager() : sceneNumber(Title),
							   scene(nullptr)
{
	scene = new class::Title;
	scene -> init();
}

SceneManager::~SceneManager()
{
}

void SceneManager::createScene(SceneNumber number)
{
	oldSceneNumber = sceneNumber;
	sceneNumber = number;
	// ���̃V�[��������
	delete scene;

	// ���̃V�[�������
	switch(sceneNumber)
	{
	case Title:
		scene = new class::Title;
		break;

	case MenuSelect:
		scene = new class::MenuSelect;
		break;

	case StageSelect:
		scene = new class::Stageselect;
		break;
	
	case EditSelect:
		scene = new class::EditSelect;
		break;

	case Game:
		scene = new class::Game;
		break;

	case Edit:
		scene = new class::Edit;
		break;

	case Pause:
		break;

	case Continue:
		break;

	case Result:
		break;

	case Ending:
		break;

	default:
		assert(!"�s���ȏ��");
		break;
	}
	
	scene -> init();
}

void SceneManager::update(void)
{
	scene -> update();
}

SceneManager::SceneNumber SceneManager::getSceneNumber(void)
{
	return sceneNumber;
}

SceneManager::SceneNumber SceneManager::getOldSceneNumber(void)
{
	return oldSceneNumber;
}
