
#ifndef __MAGICAL_BOOK_SCENE_MANAGER_H__
#define __MAGICAL_BOOK_SCENE_MANAGER_H__

#include "Scene.h"

namespace MagicalBook
{

class SceneManager
{
public:
	enum SceneNumber
	{
		Title,
		Stageselect,
		Game,
		Pause,
		Editor,
		Continue,
		Result,
		Ending,
	};

	static SceneManager* getInstance( void)
	{
		static SceneManager* instance = nullptr;
		if( !instance) { instance = new SceneManager(); }
		return instance;
	}

	SceneManager( const SceneManager&) = delete;
	const SceneManager& operator=( const SceneManager&) = delete;

	void createScene( SceneNumber number);

	void update( void);

private:
	Scene* scene;
	SceneNumber sceneNumber;

	SceneManager();
	~SceneManager();
};

}

#endif // __MAGICAL_BOOK_SCENE_MANAGER_H__