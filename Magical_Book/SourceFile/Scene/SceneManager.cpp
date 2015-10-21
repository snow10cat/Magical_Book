
#include "SceneManager.h"
#include "Title.h"
#include "Stageselect.h"
#include "Game.h"


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
	// 今のシーンを消す
	delete scene;

	// 次のシーンを作る
	switch(number)
	{
	case Title:
		scene = new class::Title;
		break;

	case Stageselect:
		scene = new class::Stageselect;
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