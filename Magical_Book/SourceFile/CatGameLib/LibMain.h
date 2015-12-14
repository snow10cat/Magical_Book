
#ifndef __CAT_GAME_LIBRARY_MAIN_H__
#define __CAT_GAME_LIBRARY_MAIN_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace CatGameLib
{

class LibShader;

class LibMain
{
public:
	/**
	 * @brief ライブラリインスタンス取得
	 *
	 * @author	Tatsuya Maeda
	 * @return  インスタンスへのポインタ
	 */
	static LibMain* getInstance(void)
	{
		static LibMain* instance = nullptr;
		if(!instance) { instance = new LibMain(); }
		return instance;
	}
	LibMain(const LibMain&) = delete;
	const LibMain& operator=(const LibMain&) = delete;

	enum ScreenMode
	{
		FullScreen,
		Window,
	};

	/**
	 *	@brief ライブラリ初期化
	 *
	 * 	@author	Tatsuya Maeda
	 */
	void initLib(void);

	/**
	 *	@brief 背景色を指定
	 *
	 *	@author	Tatsuya Maeda
	 *	@param	red		0 ~ 255の範囲の値
	 *	@param	blue	0 ~ 255の範囲の値
	 *	@param	green	0 ~ 255の範囲の値
	 *	@param	alpha	0 ~ 255の範囲の値
	 */
	void setClearColor(float red, float blue, float green, float alpha);

	/**
	 *	@brief スクリーンサイズの指定 (モニターサイズか否か)
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	isMonitorSize	true モニターサイズで描画 / false 指定サイズで描画
	 */
	void setScreenSize(bool isMonitorSize);

	/**
	 *	@brief スクリーンサイズ指定
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	width	スクリーンの横幅
	 *	@param	height	スクリーンの縦幅
	 */
	void setScreenSize(int width, int height);

	/**
	 *	@brief スクリーンモード指定
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	mode	FullScreem  or  Window
	 */
	void setScreenMode(ScreenMode mode);

	/**
	 *	@brief ウィンドウタイトルを指定
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	title	タイトル文字列
	 */
	void setWindowTitle(const char* title);

	/**
	 *	@brief ウィンドウの状態を取得
	 *
	 * 	@author	Tatsuya Maeda
	 *	@return	true 正常 / false 異常発生
	 */
	bool checkWindowState(void);

	/**
	 *	@brief 画面消去
	 *
	 *	@author	Tatsuya Maeda
	 */
	void clear(void);

	/**
	 *	@brief 描画
	 *
	 * 	@author	Tatsuya Maeda
	 */
	void draw(void);

	/**
	 *	@brief シェーダーファイルを読み込む
	 *
	 * 	@author	Tatsuya Maeda
	 *	@return	シェーダープログラムを識別する番号
	 *	@param	vertFileName 頂点シェーダーファイル名
	 *	@param	flagFileName ピクセルシェーダーファイル名
	 */
	LibShader* loadShaderProgram(const char* vertFileName, const char* flagFileName);

	/**
	 *	@brief シェーダーファイルを利用する
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	shaderNumber	シェーダープログラムを識別する番号
	 */
	void startShaderProgram(LibShader* shaderNumber);
	
	/**
	 *	@brief シェーダーファイルを利用する
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	shaderNumber	シェーダープログラムを識別する番号
	 */
	LibShader* getNowShader(void);

	LibVector2 getScreenSize(void);

	LibVector2 screenPosToWorldPos(const LibVector2& screenPos);

private:
	/**
	 * 	@brief コンストラクタ
	 *
	 * 	@author	Tatsuya Maeda
	 */
	LibMain();

	/**
	 * 	@brief デストラクタ
	 *
	 * 	@author	Tatsuya Maeda
	 */
	~LibMain();

	class Private;
	std::unique_ptr<Private> p;
};

}

#endif // __CAT_GAME_LIBRARY_MAIN_H__
