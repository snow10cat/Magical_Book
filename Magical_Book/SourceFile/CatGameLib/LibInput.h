
#ifndef __CAT_GAME_LIBRARY_INPUT_H__
#define __CAT_GAME_LIBRARY_INPUT_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

namespace CatGameLib
{

class LibInput
{
public:
	static LibInput* getInstance( void)
	{
		static LibInput* instance = nullptr;
		if( !instance) { instance = new LibInput(); }
		return instance;
	}
	LibInput( const LibInput&) = delete;
	const LibInput& operator=( const LibInput&) = delete;

	static void MouseButtonPushCallback( GLFWwindow* window, int button, int action, int mods);
	static void MouseCursorMoveCallback( GLFWwindow* window, double xpos, double ypos);
	static void MouseCursorWindowInCallback( GLFWwindow* window, int flag);
	static void MouseWheelMoveCallback( GLFWwindow* window, double xpos, double ypos);

	void update( GLFWwindow* window);

	LibVector2 getMouseVector( void);


private:

	std::vector<LibVector2> v;

	LibInput();
	~LibInput();

};

}

#endif // __CAT_GAME_LIBRARY_INPUT_H__
