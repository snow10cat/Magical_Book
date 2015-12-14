
#ifndef __CAT_GAME_LIBRARY_SHADER_H__
#define __CAT_GAME_LIBRARY_SHADER_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace CatGameLib
{

class LibShader
{
public:
	/**
	 *	@brief シェーダー停止
	 *
	 *	@author	Tatsuya Maeda
	 */
	static void shaderOff(void);

	/**
	 *	@brief コンストラクタ
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	vertFileName 頂点シェーダーファイル名
	 *	@param	vertFileName ピクセルシェーダーファイル名
	 */
	LibShader(const char* vertFileName, const char* flagFileName);

	/**
	 *	@brief デストラクタ
	 *
	 * 	@author	Tatsuya Maeda
	 */
	~LibShader();

	LibShader() = delete;
	LibShader(const LibShader&) = delete;
	const  LibShader& operator = (const LibShader&) = delete;

	/**
	 *	@brief シェーダープログラムのハンドルを取得
	 *
	 * 	@author	Tatsuya Maeda
	 */
	int getProgramHandle(void);

	void setAttributePosition(const char* valueName);
	void setAttributeUV(const char* valueName);
	void setUniformTexture(const char* valueName);

	void setAttributeHandle(const char* valueName);
	void setUniformHandle(const char* valueName);

	unsigned int getAttributePosition(void);
	unsigned int getAttributeUV(void);
	unsigned int getUniformTexture(void);

	/**
	 *	@brief 頂点シェーダーのAttribute変数のハンドルを取得
	 *
	 *	@author Tatsuya Maeda
	 *	@return	シェーダーの変数位置
	 */
	unsigned int getAttributeHandle(const char* valueName);
	
	/**
	 *	@brief 頂点シェーダーのUniform変数のハンドルを取得
	 *
	 *	@author	Tatsuya Maeda
	 *	@return	シェーダーの変数位置
	 */
	unsigned int getUniformHandle(const char* valueName);

private:
	/**
	 *	@brief シェーダー読み込み
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	fileName シェーダーファイル名
	 */
	void loadShaderFile(const char* fileName);

	/**
	 *	@brief シェーダーコンパイル
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	shaderID シェーダー識別ID
	 *	@param	fileName シェーダーファイル名
	 */
	void shaderCompile(unsigned int shaderID, const char* fileName);

	/**
	 *	@brief シェーダー読み込み
	 *
	 * 	@author	Tatsuya Maeda
	 *	@param	fileName シェーダーファイル名
	 */
	void shaderLink(const char* fileName);

	//シェーダープログラム識別ID
	unsigned int program;

	std::string attrPosName;
	std::string attrUVName;
	std::string unifTextrueName;

	std::map<std::string, unsigned int> attrValue;
	std::map<std::string, unsigned int> unifValue;
};

}

#endif // __CAT_GAME_LIBRARY_SHADER_H__