
#include "SceneManager.h"
#include "Game.h"
#include "Title.h"

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
	// ���̃V�[��������
	delete scene;

	// ���̃V�[�������
	switch(number)
	{
	case Title:
		scene = new class::Title;
		break;

	case Game:
		scene = new class::Game;
		break;

	case Pause:
		break;

	case Editor:
		break;

	case Continue:
		break;

	case Result:
		break;

	case Ending:
		break;

	default:
		break;
	}
	
	scene -> init();
}

void SceneManager::update(void)
{
	scene -> update();
}