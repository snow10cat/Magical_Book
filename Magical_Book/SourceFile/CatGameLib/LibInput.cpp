
#include "LibInput.h"

// std::pairの利用法
#define KEY_STATE_OLD first
#define KEY_STATE_NOW second

using namespace std;
using namespace CatGameLib;

static LibInput* instance = LibInput::getInstance();

class LibInput::LibGamePad
{
public:
	int stickCount; 
	vector<float> stickX;
	vector<float> stickY;
	vector<pair<bool,bool>> button;
};

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
	instance -> isMouseWheelMove = true;
	instance -> mouseWheel.x = xpos;
	instance -> mouseWheel.y = ypos;
}

LibInput::LibInput() : initPair( false, false),
					   isMouseWheelMove( false),
					   connectGamePadCount( 0),
					   window( nullptr)
{
}

LibInput::~LibInput()
{
}

void LibInput::initKeyboardState( void)
{
	for( int i = Key_0; i <= Key_9; i++)
	{
		keyboardState[i] = initPair;
	}
	for( int i = Key_A; i <= Key_Z; i++)
	{
		keyboardState[i] = initPair;
	}

	keyboardState[Key_Space]	= initPair;
	keyboardState[Key_Esc]		= initPair;
	keyboardState[Key_Up]		= initPair;
	keyboardState[Key_Down]		= initPair;
	keyboardState[Key_Left]		= initPair;
	keyboardState[Key_Right]	= initPair;
	keyboardState[Key_LShift]	= initPair;
	keyboardState[Key_RShift]	= initPair;
	keyboardState[Key_LCtrl]	= initPair;
	keyboardState[Key_RCtrl]	= initPair;
	keyboardState[Key_LAlt]		= initPair;
	keyboardState[Key_RAlt]		= initPair;
	keyboardState[Key_LSuper]	= initPair;
	keyboardState[Key_RSuper]	= initPair;
	keyboardState[Key_Tab]		= initPair;
	keyboardState[Key_Enter]	= initPair;
	keyboardState[Key_BackSpace] = initPair;
}

void LibInput::initMouseState( void)
{
	for( int i = 0; i < Mouse_Key_Num; i++)
	{
		mouseState.push_back( initPair);
	}
}

void LibInput::initGamePadState( void)
{
	while( glfwJoystickPresent( connectGamePadCount) == GL_TRUE) 
	{ 
		connectGamePadCount++;
	}

	for( int padNum = 0; padNum < connectGamePadCount; padNum++)
	{
		gamePadState.push_back( new LibGamePad());
		int stickCount = 0;
		glfwGetJoystickAxes( padNum, &stickCount);

		stickCount /= 2;

		for( int i = 0; i < stickCount; i++)
		{
			gamePadState[padNum] -> stickX.push_back( 0.0f);
			gamePadState[padNum] -> stickY.push_back( 0.0f);
		}
		
		int buttonCount = 0;
		glfwGetJoystickButtons( padNum, &buttonCount);

		for( int i = 0; i < buttonCount; i++)
		{
			gamePadState[padNum] -> button.push_back( initPair);
		}
	}
}

void LibInput::setWindow( GLFWwindow* window)
{
	this -> window = window;
}

void LibInput::initSystem( void)
{
	initKeyboardState();
	initMouseState();
	initGamePadState();
}

void LibInput::update( void)
{
	if( window == nullptr)
	{
		LibDebug::errorMessageBox( "LibInput Current Window Not Setting");
	}

	// キーボード
	for( auto i = keyboardState.begin(); i != keyboardState.end(); i++)
	{
		i -> second.KEY_STATE_OLD = i -> second.KEY_STATE_NOW;
		i -> second.KEY_STATE_NOW = glfwGetKey( window, i -> first);
	}

	// マウス
	for( int i = 0; i < Mouse_Key_Num; i++)
	{
		mouseState[i].KEY_STATE_OLD = mouseState[i].KEY_STATE_NOW;
		mouseState[i].KEY_STATE_NOW = glfwGetMouseButton( window, i);
	}

	double x;
	double y;
	glfwGetCursorPos( window, &x, &y);
	mousePosition.x = x;
	mousePosition.y = y;

	if( !isMouseWheelMove) { mouseWheel = LibVector2( 0, 0); }
	else { isMouseWheelMove = false; }

	// ゲームパッド
	for( int padNum = 0; padNum < connectGamePadCount; padNum++)
	{
		gamePadState[padNum] -> stickCount = 0;
		const float* stickArray = glfwGetJoystickAxes( padNum, &gamePadState[padNum] -> stickCount);

		for( int i = 0, j = 0; i < gamePadState[padNum] -> stickCount; i += 2, j++)
		{
			gamePadState[padNum] -> stickX[j] = stickArray[i] / 2.f + 0.5f;
			gamePadState[padNum] -> stickY[j] = stickArray[i + 1] / 2.f + 0.5f;
		}
		
		int buttonCount = 0;
		const unsigned char* buttonArray = glfwGetJoystickButtons( padNum, &buttonCount);

		for( int i = 0; i < buttonCount; i++) 
		{
			gamePadState[padNum] -> button[i].KEY_STATE_OLD = gamePadState[padNum] -> button[i].KEY_STATE_NOW;
			gamePadState[padNum] -> button[i].KEY_STATE_NOW = buttonArray[i];
		}
	}
}

LibVector2 LibInput::getMousePosition( void)
{
	return mousePosition;
}

LibVector2 LibInput::getMouseWheel( void)
{
	return mouseWheel;
}

bool LibInput::getKeyboardState( KeyBoardNumber number)
{
	return keyboardState[number].KEY_STATE_NOW;
}

bool LibInput::getKeyboardUpState( KeyBoardNumber number)
{
	if( keyboardState[number].KEY_STATE_OLD && !keyboardState[number].KEY_STATE_NOW)
	{
		return true;
	}

	return false;
}

bool LibInput::getKeyboardDownState( KeyBoardNumber number)
{
	if( !keyboardState[number].KEY_STATE_OLD && keyboardState[number].KEY_STATE_NOW)
	{
		return true;
	}

	return false;
}

bool LibInput::getMouseState( MouseNumber number)
{
	return mouseState[number].KEY_STATE_NOW;
}

bool LibInput::getMouseUpState( MouseNumber number)
{
	if( mouseState[number].KEY_STATE_OLD && !mouseState[number].KEY_STATE_NOW)
	{
		return true;
	}

	return false;
}

bool LibInput::getMouseDownState( MouseNumber number)
{
	if( !mouseState[number].KEY_STATE_OLD && mouseState[number].KEY_STATE_NOW)
	{
		return true;
	}

	return false;
}

int LibInput::getGamePadCount( void)
{
	return connectGamePadCount;
}

int LibInput::getGamePadStickCount( GamePadNumber padNumber)
{
	return gamePadState[padNumber] -> stickCount;
}

bool LibInput::getGamePadState( GamePadNumber padNumber, GamePadButtonNumber number)
{
	return gamePadState[padNumber] -> button[number].KEY_STATE_NOW;
}

bool LibInput::getGamePadUpState( GamePadNumber padNumber, GamePadButtonNumber number)
{
	if( gamePadState[padNumber] -> button[number].KEY_STATE_OLD && 
	   !gamePadState[padNumber] -> button[number].KEY_STATE_NOW)
	{
		return true;
	}

	return false;
}

bool LibInput::getGamePadDownState( GamePadNumber padNumber, GamePadButtonNumber number)
{
	if( !gamePadState[padNumber] -> button[number].KEY_STATE_OLD && 
		 gamePadState[padNumber] -> button[number].KEY_STATE_NOW)
	{
		return true;
	}

	return false;
}

LibVector2 LibInput::getGamePadStickVector( GamePadNumber padNumber, int stickNumber)
{
	float x = gamePadState[padNumber] -> stickX[stickNumber] * 2.f - 1.0f;
	float y = gamePadState[padNumber] -> stickY[stickNumber] * 2.f - 1.0f;

	if( x < 0.1f && x > -0.1f) { x = 0; }
	if( y < 0.1f && y > -0.1f) { y = 0; }

	return LibVector2( x, y);
}
