
#include "CatGameLib/CatGameLib.h"
#include "CatGameLib/ExternalLib.h"
#include "scene/SceneManager.h"

using namespace CatGameLib;

void initALure( void)
{
	// まず最初にALUREを初期化
	if ( !alureInitDevice(NULL, NULL) ) {
		std::cout << "Failed to initialize ALURE!" << std::endl;
	}
 
	// 音源を作成
	ALuint src;
	alGenSources(1, &src);
 
	// ファイルから読み込み
	ALuint buf = alureCreateBufferFromFile("ResourceFile/Sound/test.wav");
	if (buf == AL_NONE) {
		std::cout << "Failed to load from file!" << std::endl;
	}
 
	// バッファを音源に設定して
	alSourcei(src, AL_BUFFER, buf);
 
	// 再生
//	alSourcePlay(src);

	// 確保したリソースを削除
	alDeleteSources(1, &src);
	alDeleteBuffers(1, &buf);
   
	// ALUREの終了処理
	alureShutdownDevice();
}

int main()
{
	// ライブラリのインスタンス取得
	LibMain* const lib = LibMain::getInstance();

	// スクリーンサイズ指定
	lib -> setScreenSize( 1280, 720);

	// スクリーンモード指定
	lib -> setScreenMode( LibMain::ScreenMode::Window);

	// ウィンドウタイトル指定
	lib -> setWindowTitle( "Magical_Book");

	// 背景色指定
	lib -> setClearColor( 200.0f, 200.0f, 200.0f, 255.0f);

	// ライブラリ初期化
	lib -> initLib();

	// メインループ
	while( lib -> checkWindowState())
	{
		// 画面消去
		lib -> clear();

		MagicalBook::SceneManager::getInstance() -> update();

		// 描画
		lib -> draw();
	}

	return 0;
}