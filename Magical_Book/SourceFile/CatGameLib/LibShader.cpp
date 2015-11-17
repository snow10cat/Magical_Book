
#include "LibShader.h"

using namespace std;
using namespace CatGameLib;

void LibShader::shaderOff(void)
{
	glUseProgram(NULL);
}

LibShader::LibShader(const char* vertFileName, const char* flagFileName)
{
	program = glCreateProgram();
	loadShaderFile(vertFileName);
	loadShaderFile(flagFileName);
	shaderLink(vertFileName);
}	

LibShader::~LibShader()
{
}

int LibShader::getProgramHandle(void)
{
	return program;
}

void LibShader::setAttributePosition(const char* valueName)
{
	GLuint handle = glGetAttribLocation(program, valueName);
	assert(handle >= 0);
	glEnableVertexAttribArray(handle);
	attrValue[valueName] = handle;
	attrPosName = valueName;
}

void LibShader::setAttributeUV(const char* valueName)
{
	GLuint handle = glGetAttribLocation(program, valueName);
	assert(handle >= 0);
	glEnableVertexAttribArray(handle);
	attrValue[valueName] = handle;
	attrUVName = valueName;
}

void LibShader::setUniformTexture(const char* valueName)
{
	GLuint handle = glGetUniformLocation(program, valueName);
	assert(handle >= 0);
	unifValue[valueName] = handle;
	unifTextrueName = valueName;
}

void LibShader::setAttributeHandle(const char* valueName)
{
	GLuint handle = glGetAttribLocation(program, valueName);
	assert(handle >= 0);
	glEnableVertexAttribArray(handle);
	attrValue[valueName] = handle;
}

void LibShader::setUniformHandle(const char* valueName)
{
	GLuint handle = glGetUniformLocation(program, valueName);
	assert(handle >= 0);
	unifValue[valueName] = handle;
}

GLuint LibShader::getAttributePosition(void)
{
	return attrValue[attrPosName];
}

GLuint LibShader::getAttributeUV(void)
{
	return attrValue[attrUVName];
}

GLuint LibShader::getUniformTexture(void)
{
	return unifValue[unifTextrueName];
}

GLuint LibShader::getAttributeHandle(const char* valueName)
{
	GLuint handle = attrValue[valueName];
	if(handle == 0)
	{
		handle = attrValue[valueName] = glGetAttribLocation(program, valueName);
		glEnableVertexAttribArray(handle);
	}
	return handle;
}

GLuint LibShader::getUniformHandle(const char* valueName)
{
	GLuint handle = unifValue[valueName];
	if(handle == 0)
	{
		handle = unifValue[valueName] = glGetUniformLocation(program, valueName);
	}
	return handle;
}

void LibShader::loadShaderFile(const char* fileName)
{
	GLuint shader	= 0;
	string filePass = "ShaderFile/";
	filePass += fileName;
	ifstream file(filePass, ifstream::binary);

	if(file.fail())
	{
		string errorMessage = fileName;
		errorMessage += " File Open Error";
		LibDebug::errorMessageBox(errorMessage.c_str());
	}

	// ファイルパスから拡張子を抽出
	filePass.erase(0, filePass.find(".", 0));

	if(filePass == ".vsh")
	{
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if(filePass == ".fsh")
	{
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		string errorMessage = fileName;
		errorMessage += " Not Shader File";
		LibDebug::errorMessageBox(errorMessage.c_str());
	}

	// ファイルの終端に移動
	file.seekg(0, ifstream::end);

	// ファイルサイズ取得
	int fileSize = file.tellg();

	// ファイルサイズ分のメモリを確保
	GLchar* fileData = new GLchar[fileSize + 1];

	// ファイル先頭へ移動
	file.seekg(0, ifstream::beg);

	// ファイル読み込み
	file.read(fileData, fileSize);

	// ファイルを閉じる
	file.close();

	// シェーダー読み込み
	glShaderSource(shader, 1, &fileData, &fileSize);

	// シェーダーコンパイル
	shaderCompile(shader, fileName);

	// シェーダーをメインプログラムに接続
	glAttachShader(program, shader);

	// 不要となったシェーダーを削除
	glDeleteShader(shader);
}

void LibShader::shaderCompile(unsigned int shaderID, const char* fileName)
{
	GLchar* logString;
	GLint	status		 = 0;
	GLsizei logSize		 = 0;
	string	errorMessage = fileName;

	errorMessage += " Compile Error";

	// シェーダーコンパイル
	glCompileShader(shaderID);

	// ログの情報を取得
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
		
	if(logSize > 1)
	{
		// ログ格納用メモリを確保
		logString = new GLchar[logSize];

		// ログ読み込み
		glGetShaderInfoLog(shaderID, logSize, nullptr, logString);

		// エラーメッセージにログ文字列を接続
		errorMessage += "\n";
		errorMessage += logString;

		// ログを出力
		LibDebug::debugMessageLog(logString);

		// メモリ解放
		delete[] logString;
		logString = nullptr;
	}

	// シェーダーの情報を取得
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if(status == GL_FALSE)
	{
		// メッセージ出力
		LibDebug::errorMessageBox(errorMessage.c_str());
	}
}

void LibShader::shaderLink(const char* fileName)
{
	GLchar* logString;
	GLint	status = 1;
	GLsizei logSize = 0;
	string	errorMessage = fileName;

	// シェーダーをリンク
	glLinkProgram(program);

	// ログの情報を取得
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logSize);
		
	if(logSize > 1)
	{
		// ログ格納用メモリを確保
		logString = new GLchar[logSize];

		// ログ読み込み
		glGetShaderInfoLog(program, logSize, nullptr, logString);

		// エラーメッセージにログ文字列を接続
		errorMessage += "\n";
		errorMessage += logString;

		// ログを出力
		LibDebug::debugMessageLog(logString);

		// メモリ解放
		delete[] logString;
		logString = nullptr;
	}

	// シェーダーの情報を取得
	glGetShaderiv(program, GL_LINK_STATUS, &status);

	if(status == GL_FALSE)
	{
		// メッセージ出力
		LibDebug::errorMessageBox(errorMessage.c_str());
	}
}
