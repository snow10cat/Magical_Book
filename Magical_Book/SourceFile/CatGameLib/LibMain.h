
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
	 * ライブラリインスタンス取得
	 *
	 * @author	minaka1412
	 * @return  インスタンスへのポインタ
	 */
	static LibMain* getInstance( void)
	{
		static LibMain* instance = nullptr;
		if( !instance) { instance = new LibMain(); }
		return instance;
	}
	LibMain( const LibMain&) = delete;
	const LibMain& operator=( const LibMain&) = delete;

	enum ScreenMode
	{
		FullScreen,
		Window,
	};

	/**
	 *	ライブラリ初期化
	 *
	 * 	@author	minaka1412
	 */
	void initLib( void);

	/**
	 *	背景色を指定
	 *
	 *	@author	minaka1412
	 *	@param	red		0 ~ 255の範囲の値
	 *	@param	blue	0 ~ 255の範囲の値
	 *	@param	green	0 ~ 255の範囲の値
	 *	@param	alpha	0 ~ 255の範囲の値
	 */
	void setClearColor( float red, float blue, float green, float alpha);

	/**
	 *	スクリーンサイズの指定 (モニターサイズか否か)
	 *
	 * 	@author	minaka1412
	 *	@param	isMonitorSize	true モニターサイズで描画 / false 指定サイズで描画
	 */
	void setScreenSize( bool isMonitorSize);

	/**
	 *	スクリーンサイズ指定
	 *
	 * 	@author	minaka1412
	 *	@param	width	スクリーンの横幅
	 *	@param	height	スクリーンの縦幅
	 */
	void setScreenSize( int width, int height);

	/**
	 *	スクリーンモード指定
	 *
	 * 	@author	minaka1412
	 *	@param	mode	FullScreem  or  Window
	 */
	void setScreenMode( ScreenMode mode);

	/**
	 *	ウィンドウタイトルを指定
	 *
	 * 	@author	minaka1412
	 *	@param	title	タイトル文字列
	 */
	void setWindowTitle( const char* title);

	/**
	 *	ウィンドウの状態を取得
	 *
	 * 	@author	minaka1412
	 *	@return	true 正常 / false 異常発生
	 */
	bool checkWindowState( void);

	/**
	 *	画面消去
	 *
	 *	@author	minaka1412
	 */
	void clear( void);

	/**
	 *	描画
	 *
	 * 	@author	minaka1412
	 */
	void draw( void);

	/**
	 *	シェーダーファイルを読み込む
	 *
	 * 	@author	minaka1412
	 *	@return	シェーダープログラムを識別する番号
	 *	@param	vertFileName 頂点シェーダーファイル名
	 *	@param	flagFileName ピクセルシェーダーファイル名
	 */
	LibShader* loadShaderProgram( const char* vertFileName, const char* flagFileName);

	/**
	 *	シェーダーファイルを利用する
	 *
	 * 	@author	minaka1412
	 *	@param	shaderNumber	シェーダープログラムを識別する番号
	 */
	void startShaderProgram( LibShader* shaderNumber);
	
	/**
	 *	シェーダーファイルを利用する
	 *
	 * 	@author	minaka1412
	 *	@param	shaderNumber	シェーダープログラムを識別する番号
	 */
	LibShader* getNowShader( void);

	LibVector2 getScreenSize( void);

	LibVector2 screenPosToWorldPos( const LibVector2& screenPos);

private:
	/**
	 * 	コンストラクタ
	 *
	 * 	@author	minaka1412
	 */
	LibMain();

	/**
	 * 	デストラクタ
	 *
	 * 	@author	minaka1412
	 */
	~LibMain();

	class Private;
	std::unique_ptr<Private> p;
};

}

#endif // __CAT_GAME_LIBRARY_MAIN_H__
