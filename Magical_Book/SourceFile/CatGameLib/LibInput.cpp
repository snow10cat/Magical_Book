
#include "LibInput.h"

using namespace CatGameLib;

void LibInput::MouseButtonPushCallback( GLFWwindow *window, int button, int action, int mods)
{
}

void LibInput::MouseCursorMoveCallback( GLFWwindow* window, double xpos, double ypos)
{
}

void LibInput::MouseCursorWindowInCallback( GLFWwindow* window, int flag)
{
}

void LibInput::MouseWheelMoveCallback( GLFWwindow* window, double xpos, double ypos)
{
}

LibInput::LibInput()
{
}

LibInput::~LibInput()
{
}

void LibInput::update( GLFWwindow* window)
{
	static bool state=glfwGetKey( window, 'L');
	if(glfwGetKey( window, 'L')){
		if(state==false){
		state=true;
		}else{state=false;}
	}
}

LibVector2 LibInput::getMouseVector( void)
{
	LibVector2 v;
	return v;
}

