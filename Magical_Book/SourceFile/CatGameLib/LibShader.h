
#ifndef __CAT_GAME_LIBRARY_SHADER_H__
#define __CAT_GAME_LIBRARY_SHADER_H__

#include <map>
#include <string>

namespace CatGameLib
{

class LibShader
{
public:
	/**
	 *	シェーダー停止
	 */
	static void shaderOff( void);

	/**
	 *	コンストラクタ
	 *
	 * 	@author	minaka1412
	 *	@param	vertFileName 頂点シェーダーファイル名
	 *	@param	vertFileName ピクセルシェーダーファイル名
	 */
	LibShader( const char* vertFileName, const char* flagFileName);

	/**
	 *	デストラクタ
	 *
	 * 	@author	minaka1412
	 */
	~LibShader();

	LibShader() = delete;
	LibShader( const LibShader&) = delete;
	const  LibShader& operator = ( const LibShader&) = delete;

	/**
	 *	シェーダープログラムのハンドルを取得
	 *
	 * 	@author	minaka1412
	 */
	int getProgramHandle( void);

	void setAttributePosition( const char* valueName);
	void setAttributeUV( const char* valueName);
	void setUniformTexture( const char* valueName);

	void setAttributeHandle( const char* valueName);
	void setUniformHandle( const char* valueName);

	unsigned int getAttributePosition( void);
	unsigned int getAttributeUV( void);
	unsigned int getUniformTexture( void);

	/**
	 *	頂点シェーダーのAttribute変数のハンドルを取得
	 *
	 *	@author
	 *	@return	シェーダーの変数位置
	 */
	unsigned int getAttributeHandle( const char* valueName);
	
	/**
	 *	頂点シェーダーのUniform変数のハンドルを取得
	 *
	 *	@return	シェーダーの変数位置
	 */
	unsigned int getUniformHandle( const char* valueName);

private:
	/**
	 *	シェーダー読み込み
	 *
	 * 	@author	minaka1412
	 *	@param	fileName シェーダーファイル名
	 */
	void loadShaderFile( const char* fileName);

	/**
	 *	シェーダーコンパイル
	 *
	 * 	@author	minaka1412
	 *	@param	shaderID シェーダー識別ID
	 *	@param	fileName シェーダーファイル名
	 */
	void shaderCompile( unsigned int shaderID, const char* fileName);

	/**
	 *	シェーダー読み込み
	 *
	 * 	@author	minaka1412
	 *	@param	fileName シェーダーファイル名
	 */
	void shaderLink( const char* fileName);

	// シェーダープログラム識別ID
	unsigned int program;

	std::string attrPosName;
	std::string attrUVName;
	std::string unifTextrueName;

	std::map<std::string, unsigned int> attrValue;
	std::map<std::string, unsigned int> unifValue;
};

}

#endif // __CAT_GAME_LIBRARY_SHADER_H__