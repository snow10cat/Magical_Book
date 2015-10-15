
#ifndef __CAT_GAME_LIBRARY_DEBUG_H__
#define __CAT_GAME_LIBRARY_DEBUG_H__

#include "ExternalLib.h"

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
	static void errorMessageBox( const char* message)
	{
		MessageBox( NULL, message, "Error!", MB_OK);
		std::exit( 0);
	}

	/**
	 *	エラーメッセージ出力 (コンソール)
	 *
	 * 	@author	minaka1412
	 * 	@param	message		出力したい文字列
	 */
	static void debugMessageLog( const char* message)
	{
		std::string str = message;
		str += "\n";
		OutputDebugString( str.c_str());
	}
};

}

#endif // __CAT_GAME_LIBRARY_DEBUG_H__
