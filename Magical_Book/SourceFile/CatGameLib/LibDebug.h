
#ifndef __CAT_GAME_LIBRARY_DEBUG_H__
#define __CAT_GAME_LIBRARY_DEBUG_H__

#include "ExternalLib.h"
#include <functional>

namespace CatGameLib
{

class LibDebug
{
public:
	/**
	 *	エラーメッセージ出力 (メッセージボックス)
	 *
	 * 	@author	minaka1412
	 * 	@param	message		出力したい文字列
	 */
	static void errorMessageBox(const char* message)
	{
		MessageBox(NULL, message, "Error!", MB_OK);
		std::exit(0);
	}

	/**
	 *	エラーメッセージ出力 (コンソール)
	 *
	 * 	@author	minaka1412
	 * 	@param	message		出力したい文字列
	 */
	static void debugMessageLog(const char* message)
	{
		std::string str = message;
		str += "\n";
		OutputDebugString(str.c_str());
	}

	/**
	 *	エラーメッセージ出力 (コンソール)
	 *
	 * 	@author	minaka1412
	 * 	@param	message		出力したい文字列
	 */
	static void debugMessageLog(int message)
	{
		std::string str = std::to_string(message);
		str += "\n";
		OutputDebugString(str.c_str());
	}

	template < typename Func >
	static void getFunctionTime(Func func )
	{
		glfwSetTime(0.0);
		
		func();

		auto time = glfwGetTime();
		char str[256];
		sprintf(str, "%f", time);
		LibDebug::debugMessageLog(str);
	}

	static void showTime(void)
	{
		auto time = glfwGetTime();
		char str[256];
		sprintf(str, "%f", time);
		LibDebug::debugMessageLog(str);
		glfwSetTime(0.0);
	}

};

}

#endif // __CAT_GAME_LIBRARY_DEBUG_H__
