
#include "CatGameLib.h"
#include "Game/ResourceManager.h"
#include "Scene/SceneManager.h"

using namespace CatGameLib;
using namespace MagicalBook;

int main()
{
	// ライブラリのインスタンス取???
	LibMain* const lib = LibMain::getInstance();

	// スクリーンサイズ??????
	lib -> setScreenSize(1280, 720);

	// スクリーンモード指???
	lib -> setScreenMode(LibMain::ScreenMode::Window);

	// ウィンドウタイトル??????
	lib -> setWindowTitle("Magical_Book");

	// 背景色??????
	lib -> setClearColor(200.0f, 200.0f, 200.0f, 255.0f);

	// ライブラリ初期???
	lib -> initLib();

	// 共通スプライトファイル読み込み
	ResourceManager::getInstance() -> loadResource();

	SceneManager::getInstance() -> createScene(SceneManager::EditSelect);

	// メインルー???
	while(lib -> checkWindowState())
	{
		// 画面消去
		lib -> clear();

		// シーンア???プデー???
		SceneManager::getInstance() -> update();

		// 描画
		lib -> draw();
	}

	return 0;
}
