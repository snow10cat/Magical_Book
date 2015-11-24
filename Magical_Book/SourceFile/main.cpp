
#include "CatGameLib.h"
#include "Game/ResourceManager.h"
#include "Scene/SceneManager.h"

using namespace CatGameLib;
using namespace MagicalBook;

int main()
{
	//ライブラリのインスタンス取得
	LibMain* const lib = LibMain::getInstance();

	//スクリーンサイズ設定
	lib -> setScreenSize(1280, 720);

	//スクリーンモード指定
	lib -> setScreenMode(LibMain::ScreenMode::Window);

	//ウィンドウタイトル決定
	lib -> setWindowTitle("Magical_Book");

	//背景色設定
	lib -> setClearColor(200.0f, 200.0f, 200.0f, 255.0f);

	//ライブラリ初期化
	lib -> initLib();

	//共通スプライトファイル読み込み
	ResourceManager::getInstance() -> loadResource();

//	SceneManager::getInstance() -> createScene(SceneManager::EditSelect);

	//メインループ
	while(lib -> checkWindowState())
	{
		//画面消去
		lib -> clear();

		//シーンアップデート
		SceneManager::getInstance() -> update();

		//描画
		lib -> draw();
	}

	return 0;
}
